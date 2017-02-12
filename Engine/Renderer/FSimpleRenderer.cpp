/*
 * FSimpleRenderer.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: root
 */

#include "FSimpleRenderer.h"
#include <exception>
#include <iostream>
#include <fstream>
#include <limits>


FSimpleRenderer::FSimpleRenderer( FWindow& window ) :
	_window( window )
{
	// Move one level up or throw exception, ctor should fail if initialization is not completed
	try {
		createInstance();
		selectGPU();
		createLogicalDevice();
		createSurface();
		createSwapChain();
		createImageViews();
		createRenderPass();
		createGraphicPipelines();
		createFrameBuffers();
		createCommandPool();
		createCommandBuffers();
		createSemaphores();
	}
	catch ( std::runtime_error& err ) {
		std::cout << err.what() << std::endl;
	}
}

FSimpleRenderer::~FSimpleRenderer() {
	vkDestroySemaphore( _device, _image_available_sem, nullptr );
	vkDestroySemaphore( _device, _render_finished_sem, nullptr );

	vkDestroyCommandPool( _device, _command_pool, nullptr );

	for ( size_t i = 0; i<_frame_buffers.size(); i++ ) {
		vkDestroyFramebuffer( _device, _frame_buffers[i], nullptr );
	}

	vkDestroyPipeline( _device, _graphic_pipeline, nullptr );
	vkDestroyRenderPass( _device, _render_pass, nullptr );
	vkDestroyPipelineLayout( _device, _pipeline_layout, nullptr );

	for ( size_t i = 0; i<_image_views.size(); i++ ) {
		vkDestroyImageView( _device, _image_views[i], nullptr );
	}

	vkDestroySwapchainKHR( _device, _swapchain, nullptr );
	vkDestroySurfaceKHR( _instance, _surface, nullptr );
	vkDestroyDevice( _device, nullptr );
	vkDestroyInstance( _instance, nullptr );

	_command_pool		= nullptr;
	_graphic_pipeline	= nullptr;
	_pipeline_layout	= nullptr;
	_swapchain			= nullptr;
	_surface			= nullptr;
	_device 			= nullptr;
	_instance 			= nullptr;
}

void FSimpleRenderer::RenderFrame() {
	/* Aquire image from the swap chain */
	uint32_t image_index = 0;	// index to available swap chain image
	vkAcquireNextImageKHR( _device, _swapchain, std::numeric_limits<uint64_t>::max(),
			_image_available_sem, VK_NULL_HANDLE, &image_index );

    VkSemaphore wait_semaphores[] = { _image_available_sem };
    VkSemaphore signal_semaphores[] = { _render_finished_sem };
    VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    VkSubmitInfo submit_info = {};
    submit_info.sType 					= VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.waitSemaphoreCount 		= 1;
    submit_info.pWaitSemaphores 		= wait_semaphores;
    submit_info.pWaitDstStageMask 		= wait_stages;
    submit_info.commandBufferCount 		= 1;
    submit_info.pCommandBuffers 		= &_command_buffers[image_index];
    submit_info.signalSemaphoreCount	= 1;
    submit_info.pSignalSemaphores 		= signal_semaphores;

    auto result = vkQueueSubmit( _graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
    if ( VK_SUCCESS != result ){
        throw std::runtime_error( "Vulkan ERROR: Could not submit graphic queue" );
    }

    VkPresentInfoKHR present_info = {};
    present_info.sType 				= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores 	= signal_semaphores;

    VkSwapchainKHR swap_chains[] = { _swapchain };
    present_info.swapchainCount	= 1;
    present_info.pSwapchains 	= swap_chains;
    present_info.pImageIndices 	= &image_index;

    vkQueuePresentKHR( _present_queue, &present_info );
}

std::vector<char> FSimpleRenderer::ReadStreamFromFile( const std::string& filename ) {
	std::ifstream  file( filename, std::ios::ate | std::ios::binary );

	if ( !file.is_open() ) {
		throw std::runtime_error("Renderer could not open file.");
	}

	size_t file_size = static_cast<size_t>(file.tellg());
	std::vector<char> buffer( file_size );

	file.seekg(0);
	file.read( buffer.data(), file_size );
	file.close();

	return buffer;
}

void FSimpleRenderer::createInstance() {
	// Todo: Consider setting it as a member
	std::vector<const char*> instance_enabled_extensions;
	instance_enabled_extensions.push_back( VK_KHR_SURFACE_EXTENSION_NAME );
	instance_enabled_extensions.push_back( "VK_KHR_xcb_surface" );

	VkApplicationInfo application_info = {};
	application_info.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	application_info.pApplicationName	= "Harambe!";
	application_info.pEngineName		= "VuEngine";
	application_info.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
	application_info.apiVersion			= VK_API_VERSION_1_0;

	VkInstanceCreateInfo instance_create_info = {};
	instance_create_info.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pApplicationInfo			= &application_info;
	instance_create_info.enabledExtensionCount		= instance_enabled_extensions.size();
	instance_create_info.ppEnabledExtensionNames	= instance_enabled_extensions.data();

	auto result = vkCreateInstance( &instance_create_info, nullptr, &_instance );
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error( "Vulkan: Could not create instance." );
	}
}

void FSimpleRenderer::selectGPU() {
	uint32_t device_count = 0;
	auto result = vkEnumeratePhysicalDevices( _instance, &device_count, nullptr );
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error( "Vulkan: Could not query the number of physical devices." );
	}

	if ( 0 == device_count ) {
		throw std::runtime_error( "Vulkan: Could not detect any physical device." );
	}

	std::vector<VkPhysicalDevice> physical_devices( device_count );
	result = vkEnumeratePhysicalDevices( _instance, &device_count, physical_devices.data() );
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error( "Vulkan: Could not enumerate physical devices." );
	}

	// Todo: Some fancy device selection would be appreciated, for now we select firs one
	_physical_device = physical_devices[0];

	uint32_t queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties( _physical_device, &queue_family_count, nullptr);

	std::vector<VkQueueFamilyProperties> queue_families( queue_family_count );
	vkGetPhysicalDeviceQueueFamilyProperties( _physical_device, &queue_family_count, queue_families.data() );

	/* Find suitable queue family index */ //Todo: refactor
	size_t i = 0;
	for ( const auto& q_family : queue_families ) {
	    if (q_family.queueCount > 0 && q_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
	        _graphics_family_index = i;

	        // Note: ERROR PRONE <<< check here for some errors
	        VkBool32 present_support = false;
			vkGetPhysicalDeviceSurfaceSupportKHR( _physical_device, i, _surface, &present_support);

			if ( q_family.queueCount > 0 && present_support ) {
				_present_family_index = i;
			}
	    }
        i++;
	}

	std::cout << "Graphic: " << _graphics_family_index << std::endl;
	std::cout << "Present: " << _present_family_index << std::endl;
}

void FSimpleRenderer::createLogicalDevice() {
	// Todo: Consider setting it as a member
	std::vector<const char*> device_enabled_extensions;
	device_enabled_extensions.push_back( VK_KHR_SWAPCHAIN_EXTENSION_NAME );

	float queue_priorities[] = { 1.0f };
	VkDeviceQueueCreateInfo queue_create_info = {};
	queue_create_info.sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueCount		= 1;
	queue_create_info.pQueuePriorities	= queue_priorities;

	VkDeviceCreateInfo device_create_info = {};
	device_create_info.sType					= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.queueCreateInfoCount		= 1;
	device_create_info.pQueueCreateInfos		= &queue_create_info;
	device_create_info.ppEnabledExtensionNames	= device_enabled_extensions.data();
	device_create_info.enabledExtensionCount	= device_enabled_extensions.size();

	auto result = vkCreateDevice( _physical_device, &device_create_info, nullptr, &_device );
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error( "Vulkan: Could not create devices." );
	}

	vkGetDeviceQueue( _device, _graphics_family_index, 0, &_graphics_queue );
	vkGetDeviceQueue( _device, _present_family_index, 0, &_present_queue );
}

void FSimpleRenderer::createSurface() {
	{
		/*auto fpCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR)
				vkGetInstanceProcAddr( _instance, "vkCreateXcbSurfaceKHR");*/
		VkXcbSurfaceCreateInfoKHR surface_create_info = {};
		surface_create_info.sType		= VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
		surface_create_info.connection	= _window.GetConnection();
		surface_create_info.window		= _window.GetWindow();

		auto result = vkCreateXcbSurfaceKHR( _instance, &surface_create_info, nullptr, &_surface );
		if ( VK_SUCCESS != result ) {
			throw std::runtime_error( "Vulkan: Could not create surface." );
		}
	}

	{
		uint32_t format_count = 0;
		auto fpGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)
				vkGetInstanceProcAddr( _instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
		fpGetPhysicalDeviceSurfaceFormatsKHR( _physical_device, _surface, &format_count, nullptr );

		if ( 0 == format_count ) {
			throw std::runtime_error( "Vulkan: Got 0 format count available." );
		}

		std::vector<VkSurfaceFormatKHR> surface_formats( format_count );
		fpGetPhysicalDeviceSurfaceFormatsKHR( _physical_device, _surface, &format_count,
				surface_formats.data() );

		if ( VK_FORMAT_UNDEFINED == surface_formats[0].format ) {
			_surface_format.format		= VK_FORMAT_B8G8R8A8_UNORM;
			_surface_format.colorSpace	= VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		}
		else {
			_surface_format				= surface_formats[0];
		}
	}
}

void FSimpleRenderer::createSwapChain() {
	{
		VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
		{
			uint32_t present_mode_count = 0;
			vkGetPhysicalDeviceSurfacePresentModesKHR( _physical_device, _surface,
					&present_mode_count, nullptr );

			std::vector<VkPresentModeKHR> present_mode_list( present_mode_count );
			vkGetPhysicalDeviceSurfacePresentModesKHR( _physical_device, _surface,
					&present_mode_count, present_mode_list.data() );

			for ( auto mode : present_mode_list ) {
				if ( VK_PRESENT_MODE_MAILBOX_KHR == mode ) {
					present_mode = mode;
					break;
				}
			}
		}
		// Todo: wtf man? hardcoded?
		_swapchain_extent.height = 300;
		_swapchain_extent.width = 400;

		VkSwapchainCreateInfoKHR swapchain_create_info {};
		swapchain_create_info.sType					= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchain_create_info.surface				= _surface;
		swapchain_create_info.minImageCount			= 2;
		swapchain_create_info.imageFormat			= _surface_format.format;
		swapchain_create_info.imageColorSpace		= _surface_format.colorSpace;
		//swapchain_create_info.imageExtent.width		= 90;
		//swapchain_create_info.imageExtent.height	= 90;
		swapchain_create_info.imageExtent			= _swapchain_extent;
		swapchain_create_info.imageArrayLayers		= 1;
		swapchain_create_info.imageUsage			= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchain_create_info.imageSharingMode		= VK_SHARING_MODE_EXCLUSIVE;
		swapchain_create_info.queueFamilyIndexCount	= 0;
		swapchain_create_info.pQueueFamilyIndices	= nullptr;
		swapchain_create_info.preTransform			= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		swapchain_create_info.compositeAlpha		= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchain_create_info.presentMode			= present_mode;
		swapchain_create_info.clipped				= VK_TRUE;
		swapchain_create_info.oldSwapchain			= VK_NULL_HANDLE;

		vkCreateSwapchainKHR( _device, &swapchain_create_info, nullptr, &_swapchain );

		uint32_t swapchain_image_count = 2;
		auto result = vkGetSwapchainImagesKHR( _device, _swapchain, &swapchain_image_count, nullptr );
		if ( VK_SUCCESS != result ) {
			throw std::runtime_error( "Vulkan: Could not get swapchain images" );
		}

		/* Retrive handles to the images in swapchain */
		uint32_t image_count = 0;
		vkGetSwapchainImagesKHR( _device, _swapchain, &image_count, nullptr );
		_swapchain_images.resize( image_count );
		vkGetSwapchainImagesKHR( _device, _swapchain, &image_count, _swapchain_images.data() );
	}
}

void FSimpleRenderer::createImageViews() {
	_image_views.resize( _swapchain_images.size() );

	for ( uint32_t i = 0; i<_swapchain_images.size(); i++ ) {
		// Todo: Actually this struct can be move outside loop
		VkImageViewCreateInfo image_create_info = {};
		image_create_info.sType 			= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		image_create_info.image				= _swapchain_images[i];
		image_create_info.viewType			= VK_IMAGE_VIEW_TYPE_2D;
		image_create_info.format			= _surface_format.format;
		image_create_info.components.r		= VK_COMPONENT_SWIZZLE_IDENTITY;
		image_create_info.components.g		= VK_COMPONENT_SWIZZLE_IDENTITY;
		image_create_info.components.b		= VK_COMPONENT_SWIZZLE_IDENTITY;
		image_create_info.components.a		= VK_COMPONENT_SWIZZLE_IDENTITY;
		image_create_info.subresourceRange.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
		image_create_info.subresourceRange.baseMipLevel		= 0;
		image_create_info.subresourceRange.layerCount		= 1;
		image_create_info.subresourceRange.levelCount		= 1;
		image_create_info.subresourceRange.baseArrayLayer	= 0;

		auto result = vkCreateImageView( _device, &image_create_info, nullptr, &_image_views[i] );
		if ( VK_SUCCESS != result ) {
			throw std::runtime_error( "Vulkan: Could not create image view." );
		}
	}
}

void FSimpleRenderer::createRenderPass() {
	VkAttachmentDescription color_attachment = {};
	color_attachment.format 		= _surface_format.format;
	color_attachment.samples 		= VK_SAMPLE_COUNT_1_BIT;
	color_attachment.loadOp 		= VK_ATTACHMENT_LOAD_OP_CLEAR;
	color_attachment.storeOp 		= VK_ATTACHMENT_STORE_OP_STORE;
	color_attachment.stencilLoadOp 	= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	color_attachment.stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	color_attachment.initialLayout 	= VK_IMAGE_LAYOUT_UNDEFINED;
	color_attachment.finalLayout 	= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference color_attachment_ref = {};
	color_attachment_ref.attachment = 0;
	color_attachment_ref.layout 	= VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass_desc = {};
	subpass_desc.pipelineBindPoint 		= VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass_desc.colorAttachmentCount 	= 1;
	subpass_desc.pColorAttachments 		= &color_attachment_ref;

	VkRenderPassCreateInfo render_pass_info = {};
	render_pass_info.sType 				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	render_pass_info.attachmentCount 	= 1;
	render_pass_info.pAttachments 		= &color_attachment;
	render_pass_info.subpassCount 		= 1;
	render_pass_info.pSubpasses 		= &subpass_desc;

	auto result = vkCreateRenderPass( _device, &render_pass_info, nullptr, &_render_pass);
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error( "Vulkan ERROR: Could not create render pass" );
	}
}

void FSimpleRenderer::createGraphicPipelines() {
	/* Load shaders */
	auto vert_shader_code = ReadStreamFromFile("Shaders/vert.spv");
	auto frag_shader_code = ReadStreamFromFile("Shaders/frag.spv");

	VkShaderModule vert_shad_module = VK_NULL_HANDLE;
	VkShaderModule frag_shad_module = VK_NULL_HANDLE;

	createShaderModule( vert_shader_code, vert_shad_module );
	createShaderModule( frag_shader_code, frag_shad_module );

	/* Make shaders aware of each other */ // Todo: This has to be encapsulated into func
	VkPipelineShaderStageCreateInfo vert_shad_stage_info = {};
	vert_shad_stage_info.sType 	= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vert_shad_stage_info.stage 	= VK_SHADER_STAGE_VERTEX_BIT;
	vert_shad_stage_info.module = vert_shad_module;
	vert_shad_stage_info.pName 	= "main";

	VkPipelineShaderStageCreateInfo frag_shad_stage_info = {};
	frag_shad_stage_info.sType 	= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	frag_shad_stage_info.stage 	= VK_SHADER_STAGE_FRAGMENT_BIT;
	frag_shad_stage_info.module = frag_shad_module;
	frag_shad_stage_info.pName 	= "main";

	VkPipelineShaderStageCreateInfo shader_stages[] = {
			vert_shad_stage_info, frag_shad_stage_info };

	/* Format of the vertex data passed to the vertex shader */
	VkPipelineVertexInputStateCreateInfo vert_input_info = {};
	vert_input_info.sType 							= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vert_input_info.vertexBindingDescriptionCount	= 0;
	vert_input_info.pVertexBindingDescriptions		= nullptr;
	vert_input_info.vertexAttributeDescriptionCount	= 0;
	vert_input_info.pVertexAttributeDescriptions	= nullptr;

	/* Geometry type to be drawn */
	VkPipelineInputAssemblyStateCreateInfo input_assembly_info = {};
	input_assembly_info.sType 					= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	input_assembly_info.topology 				= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	input_assembly_info.primitiveRestartEnable	= VK_FALSE;

	/* Region of the framebuffer that the output will be rendered to */
	VkViewport viewport = {};
	viewport.x 			= 0.0f;
	viewport.y 			= 0.0f;
	viewport.width 		= static_cast<float>(_swapchain_extent.width);
	viewport.height 	= static_cast<float>(_swapchain_extent.height);
	viewport.minDepth 	= 0.0f;
	viewport.maxDepth	= 1.0f;

	VkRect2D scissor = {};
	scissor.offset	= {0, 0};
	scissor.extent 	= _swapchain_extent;

	VkPipelineViewportStateCreateInfo viewport_state_info = {};
	viewport_state_info.sType 			= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewport_state_info.viewportCount 	= 1;
	viewport_state_info.pViewports 		= &viewport;
	viewport_state_info.scissorCount 	= 1;
	viewport_state_info.pScissors 		= &scissor;

	/* Rasterizer configuration */
	VkPipelineRasterizationStateCreateInfo rasterizer_info = {};
	rasterizer_info.sType 					= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer_info.depthClampEnable 		= VK_FALSE;
	rasterizer_info.rasterizerDiscardEnable	= VK_FALSE;
	rasterizer_info.polygonMode 			= VK_POLYGON_MODE_FILL;
	rasterizer_info.lineWidth 				= 1.0f;
	rasterizer_info.cullMode 				= VK_CULL_MODE_BACK_BIT;
	rasterizer_info.frontFace 				= VK_FRONT_FACE_CLOCKWISE;
	rasterizer_info.depthBiasEnable 		= VK_FALSE;
	rasterizer_info.depthBiasConstantFactor = 0.0f;
	rasterizer_info.depthBiasClamp 			= 0.0f;
	rasterizer_info.depthBiasSlopeFactor 	= 0.0f;

	/* Multisampling configuration */
	VkPipelineMultisampleStateCreateInfo multisample_info = {};
	multisample_info.sType 					= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisample_info.sampleShadingEnable 	= VK_FALSE;
	multisample_info.rasterizationSamples 	= VK_SAMPLE_COUNT_1_BIT;
	multisample_info.minSampleShading 		= 1.0f;
	multisample_info.pSampleMask 			= nullptr;
	multisample_info.alphaToCoverageEnable	= VK_FALSE;
	multisample_info.alphaToOneEnable 		= VK_FALSE;

	/* Depth and stencil buffer configuration */
	// Todo: not used for now

	/* Blending options */
	VkPipelineColorBlendAttachmentState color_blend_attachment = {};
	color_blend_attachment.colorWriteMask	= VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	color_blend_attachment.blendEnable 		= VK_FALSE;

	VkPipelineColorBlendStateCreateInfo color_blending_info = {};
	color_blending_info.sType 				= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	color_blending_info.logicOpEnable 		= VK_FALSE;
	color_blending_info.logicOp 			= VK_LOGIC_OP_COPY;
	color_blending_info.attachmentCount 	= 1;
	color_blending_info.pAttachments 		= &color_blend_attachment;
	color_blending_info.blendConstants[0]	= 0.0f;
	color_blending_info.blendConstants[1] 	= 0.0f;
	color_blending_info.blendConstants[2] 	= 0.0f;
	color_blending_info.blendConstants[3] 	= 0.0f;

	VkPipelineLayoutCreateInfo pipeline_layout_info = {};
	pipeline_layout_info.sType 					= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipeline_layout_info.setLayoutCount 		= 0;
	pipeline_layout_info.pushConstantRangeCount	= 0;

	{
		auto result = vkCreatePipelineLayout( _device, &pipeline_layout_info,
				nullptr, &_pipeline_layout );
		if ( VK_SUCCESS != result ) {
			throw std::runtime_error( "Vulkan ERROR: Could not create pipeline layout" );
		}
	}

	/* Create pipeline itself */
	VkGraphicsPipelineCreateInfo pipeline_info = {};
	pipeline_info.sType 				= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline_info.stageCount 			= 2;
	pipeline_info.pStages 				= shader_stages;
	pipeline_info.pVertexInputState 	= &vert_input_info;
	pipeline_info.pInputAssemblyState	= &input_assembly_info;
	pipeline_info.pViewportState 		= &viewport_state_info;
	pipeline_info.pRasterizationState 	= &rasterizer_info;
	pipeline_info.pMultisampleState 	= &multisample_info;
	pipeline_info.pDepthStencilState 	= nullptr;
	pipeline_info.pColorBlendState 		= &color_blending_info;
	pipeline_info.pDynamicState 		= nullptr;
	pipeline_info.layout 				= _pipeline_layout;
	pipeline_info.renderPass 			= _render_pass;
	pipeline_info.subpass 				= 0;
	pipeline_info.basePipelineHandle 	= VK_NULL_HANDLE;
	pipeline_info.basePipelineIndex 	= -1;

	{
		auto result = vkCreateGraphicsPipelines( _device, VK_NULL_HANDLE, 1,
				&pipeline_info, nullptr, &_graphic_pipeline);
		if ( VK_SUCCESS != result ) {
			throw std::runtime_error( "Vulkan ERROR: Could not create graphic pipeline" );
		}
	}
}

void FSimpleRenderer::createFrameBuffers() {
	_frame_buffers.resize( _image_views.size() );

	for (size_t i = 0; i < _image_views.size(); i++) {
	    VkImageView attachments[] = { _image_views[i] };

	    VkFramebufferCreateInfo frame_buffer_info = {};
	    frame_buffer_info.sType 			= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	    frame_buffer_info.renderPass 		= _render_pass;
	    frame_buffer_info.attachmentCount 	= 1;
	    frame_buffer_info.pAttachments 		= attachments;
	    frame_buffer_info.width 			= _swapchain_extent.width;
	    frame_buffer_info.height 			= _swapchain_extent.height;
	    frame_buffer_info.layers 			= 1;

	    auto result = vkCreateFramebuffer( _device, &frame_buffer_info, nullptr,
	    		&_frame_buffers[i] );
	    if ( VK_SUCCESS != result ) {
	    	throw std::runtime_error( "Vulkan ERROR: Could not create frame buffer" );
	    }
	}
}

void FSimpleRenderer::createCommandPool() {
	VkCommandPoolCreateInfo command_pool_info = {};
	command_pool_info.sType 			= VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	command_pool_info.queueFamilyIndex	= _graphics_family_index;
	command_pool_info.flags 			= 0;

	auto result = vkCreateCommandPool( _device, &command_pool_info, nullptr, &_command_pool);
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error( "Vulkan ERROR: Could not create command pool" );
	}
}

void FSimpleRenderer::createCommandBuffers() {
	_command_buffers.resize( _frame_buffers.size() );

	VkCommandBufferAllocateInfo buffer_alloc_info = {};
	buffer_alloc_info.sType 				= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	buffer_alloc_info.commandPool			= _command_pool;
	buffer_alloc_info.level 				= VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	buffer_alloc_info.commandBufferCount 	= static_cast<uint32_t>( _command_buffers.size() );

	auto result = vkAllocateCommandBuffers( _device, &buffer_alloc_info, _command_buffers.data() );
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error( "Vulkan ERROR: Could not allocate command buffers" );
	}

	for (size_t i = 0; i<_command_buffers.size(); i++) {
		VkCommandBufferBeginInfo cmd_buf_begin_info = {};
		cmd_buf_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	    cmd_buf_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	    /* Start recording command buffer */
	    vkBeginCommandBuffer( _command_buffers[i], &cmd_buf_begin_info );

	    VkRenderPassBeginInfo render_pass_info = {};
	    render_pass_info.sType 				= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	    render_pass_info.renderPass 		= _render_pass;
	    render_pass_info.framebuffer 		= _frame_buffers[i];
	    render_pass_info.renderArea.offset	= {0, 0};
	    render_pass_info.renderArea.extent 	= _swapchain_extent;

	    VkClearValue clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
	    render_pass_info.clearValueCount	= 1;
	    render_pass_info.pClearValues 		= &clear_color;

	    vkCmdBeginRenderPass( _command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE );
	    vkCmdBindPipeline( _command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphic_pipeline );
	    vkCmdDraw( _command_buffers[i], 3, 1, 0, 0 );
	    vkCmdEndRenderPass( _command_buffers[i] );

	    auto result = vkEndCommandBuffer( _command_buffers[i] );
	    if ( VK_SUCCESS != result ) {
	    	throw std::runtime_error( "Vulkan ERROR: Could not end recording commands" );
	    }
	}
}

void FSimpleRenderer::createSemaphores() {
	VkSemaphoreCreateInfo semaphore_info = {};
	semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	{
		auto result = vkCreateSemaphore( _device, &semaphore_info, nullptr,
				&_image_available_sem );
		if ( VK_SUCCESS != result ) {
			throw std::runtime_error( "Vulkan ERROR: Could not create image semaphore" );
		}
	}

	{
		auto result = vkCreateSemaphore( _device, &semaphore_info, nullptr,
				&_render_finished_sem );
		if ( VK_SUCCESS != result ) {
			throw std::runtime_error( "Vulkan ERROR: Could not create render semaphore" );
		}
	}
}

void FSimpleRenderer::createShaderModule( const std::vector<char>& shaderCode,
			VkShaderModule& shaderModule ) {
	VkShaderModuleCreateInfo create_info = {};
	create_info.sType			= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize		= shaderCode.size();
	// Risk of dumping into adjacent memory, what to do?
	create_info.pCode			= (uint32_t*)shaderCode.data();

	auto result = vkCreateShaderModule( _device, &create_info, nullptr, &shaderModule );
	if ( VK_SUCCESS != result ) {
		throw std::runtime_error("Vulkan ERROR: Could not create shader module");
	}
}























