/*
 * FSimpleRenderer.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: root
 */

#include "FSimpleRenderer.h"
#include <exception>
#include <iostream>


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
	}
	catch ( std::runtime_error& err ) {
		std::cout << err.what() << std::endl;
	}
}

FSimpleRenderer::~FSimpleRenderer() {
	for ( uint32_t i = 0; i<_image_views.size(); i++ ) {
		vkDestroyImageView( _device, _image_views[i], nullptr );
	}

	vkDestroySwapchainKHR( _device, _swapchain, nullptr );
	vkDestroySurfaceKHR( _instance, _surface, nullptr );
	vkDestroyDevice( _device, nullptr );
	vkDestroyInstance( _instance, nullptr );

	_swapchain	= nullptr;
	_surface	= nullptr;
	_device 	= nullptr;
	_instance 	= nullptr;
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
		_swapchain_extent.height = 90;
		_swapchain_extent.width = 90;

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

void FSimpleRenderer::createGraphicPipelines() {

}





















