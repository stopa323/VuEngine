/*
 * FSimpleRenderer.h
 *
 *  Created on: Feb 7, 2017
 *      Author: root
 */

#ifndef ENGINE_RENDERER_FSIMPLERENDERER_H_
#define ENGINE_RENDERER_FSIMPLERENDERER_H_

#define VK_USE_PLATFORM_XCB_KHR
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "../Window/FWindow.h"
#include "FShaderManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <memory>
#include <vector>


class FSimpleRenderer {
public:
	FSimpleRenderer( FWindow& window );
	virtual ~FSimpleRenderer();

	void RenderFrame();

	// Todo: move to separate Loader class
	static std::vector<char> ReadStreamFromFile( const std::string& filename );

	// Todo: temporary
	struct SUniformBufferObject {
		glm::mat4 model_mtx;
		glm::mat4 view_mtx;
		glm::mat4 projection_mtx;
	};
	SUniformBufferObject ubo = {};
	// Todo: temporary
	void UpdateUniformBuffer();

private:
	void createInstance();
	void selectGPU();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createDescriptorSetLayout();
	void createGraphicPipelines();
	void createFrameBuffers();
	void createCommandPool();
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffer();
	void createDescriptorPool();
	void createDescriptorSet();
	void createCommandBuffers();
	void createSemaphores();

	void createShaderModule( const std::vector<char>& shaderCode,
			VkShaderModule& shaderModule );

	/**
	 * Combine requirements of the buffer and application and find right type of
	 * memory to use in terms of allowed operations and performance characteristics.
	 */
	uint32_t getSuitableMemoryType( uint32_t typeFilter,
			VkMemoryPropertyFlags properities );

	void createBuffer( VkDeviceSize size, VkBuffer& buffer, VkDeviceMemory& bufferMemory,
			VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags propertyFlags );

	void bufferToBufferCopy( VkBuffer sourceBuffer, VkBuffer destinationBuffer,
			VkDeviceSize size );

	VkInstance						_instance					= VK_NULL_HANDLE;
	VkPhysicalDevice				_physical_device			= VK_NULL_HANDLE;
	VkDevice						_device						= VK_NULL_HANDLE;
	VkSurfaceKHR					_surface					= VK_NULL_HANDLE;
	VkSurfaceFormatKHR				_surface_format				= {};
	VkSwapchainKHR					_swapchain					= VK_NULL_HANDLE;
	std::vector<VkImage>			_swapchain_images;
	VkExtent2D						_swapchain_extent			= {};
	std::vector<VkImageView>		_image_views;
	std::vector<VkFramebuffer>		_frame_buffers;
	VkDescriptorSetLayout			_descriptor_set_layout		= VK_NULL_HANDLE;
	VkDescriptorPool				_descriptor_pool			= VK_NULL_HANDLE;
	VkDescriptorSet					_descriptor_set				= VK_NULL_HANDLE;
	VkPipelineLayout				_pipeline_layout			= VK_NULL_HANDLE;
	VkRenderPass					_render_pass				= VK_NULL_HANDLE;
	VkPipeline						_graphic_pipeline			= VK_NULL_HANDLE;
	VkCommandPool					_command_pool				= VK_NULL_HANDLE;
	std::vector<VkCommandBuffer>	_command_buffers; // automatically freed when their command pool destroyed
	VkSemaphore						_image_available_sem		= VK_NULL_HANDLE;
	VkSemaphore						_render_finished_sem		= VK_NULL_HANDLE;

	// Todo: aggregate
	VkBuffer						_vertex_buffer				= VK_NULL_HANDLE;
	VkDeviceMemory					_vertex_buffer_mem			= VK_NULL_HANDLE;
	VkBuffer						_index_buffer				= VK_NULL_HANDLE;
	VkDeviceMemory					_index_buffer_mem			= VK_NULL_HANDLE;

	VkBuffer						_uniform_buffer				= VK_NULL_HANDLE;
	VkDeviceMemory					_uniform_buffer_mem			= VK_NULL_HANDLE;
	VkBuffer						_uniform_staging_buffer		= VK_NULL_HANDLE;
	VkDeviceMemory					_uniform_staging_buffer_mem	= VK_NULL_HANDLE;

	uint32_t						_graphics_family_index		= 0;
	uint32_t						_present_family_index		= 0;

	VkQueue 						_graphics_queue				= VK_NULL_HANDLE;
	VkQueue 						_present_queue				= VK_NULL_HANDLE;

	FWindow& 						_window;
	std::shared_ptr<FShaderManager>	_shader_manager;

	// Note: temporary, this will be moved to UObject
	const std::vector<SVertex> _vertices = {
	    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> _indices = { 0, 1, 2, 2, 3, 0};

};

#endif /* ENGINE_RENDERER_FSIMPLERENDERER_H_ */
