set( dir "${CMAKE_CURRENT_SOURCE_DIR}" )

list(
		APPEND src
		"${dir}/funs.cpp"
		"${dir}/CShader.cpp"
		"${dir}/CRenderer.cpp"
		"${dir}/CVertexBuffer.cpp"
		"${dir}/CElementBuffer.cpp"
		"${dir}/CVertexBufferLayout.cpp"
		"${dir}/CVertexArray.cpp"
		"${dir}/CImageLoader.cpp"
		"${dir}/CTexture.cpp"
		"${dir}/CCamera.cpp"
		"${dir}/CApplication.cpp"
		"${dir}/main.cpp"
	)

set( src "${src}" PARENT_SCOPE )
