void FontRenderer::draw(const glm::mat4& projection)
{
	std::lock_guard<std::mutex> lock(m_queueManipMutex);
	const bool isBlend = glIsEnabled(GL_BLEND);

	glDisable(GL_DEPTH_TEST);
	if(!isBlend){
		//  I need blending
		glEnable(GL_BLEND);
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (!m_shader) throw font_error("provided shader is invalid !");
	//bind the shader
	m_shader->begin();
	//upload projection	
	m_shader->unsafeUniformVariable("projection",projection);

	//upload text color
	//m_shader->uniformVariable("textColor",glm::vec3(color));

	//bind active texture unit and Vertex Arrays
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_VAO);
	
	//iterate over each position in the map (note that the map automagically groups the same characters)
	decltype(m_renderQueue.equal_range(0)) range;
	for (auto i = m_renderQueue.begin(); i != m_renderQueue.end(); i = range.second)
	{
		range = m_renderQueue.equal_range(i->first);
	
		//bind the texture for this specific character
		glBindTexture(GL_TEXTURE_2D, i->first);


		glBindBuffer(GL_ARRAY_BUFFER,m_VBO);

		//get number of Chars in range
		const std::size_t range_size = m_renderQueue.count(i->first);

		//orphan buffer
		glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*6*4*range_size,NULL,GL_DYNAMIC_DRAW);
		
		//get buffer into physical space
		GLfloat* buffer = reinterpret_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY));

		//copy all char vertex datas into buffer
		int j = 0;
		for (auto d = range.first; d != range.second; ++d)
		{
			__pfast_memcpy(&buffer[6*4*j++],d->second.first.data(),6*4*sizeof(GLfloat));
		}

		//release buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		
		j=0;
		for(auto k = range.first;k != range.second;++k)
		{

			//Replacement for the code commented out below
			m_shader->unsafeUniformVariable("textColor",glm::vec3(k->second.second));

			//way to slow the registry takes too long for lots of operations
			//we can assume the shader is bound anyway as we own the rendering thread whilst in this function
			//and we bound it earlier
			//m_shader->uniformVariable("textColor",glm::vec3(k->second.second));
			glDrawArrays(GL_TRIANGLES,6*j++,6);
		}
	}

	//clear render state
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_shader->end();

	//delete all drawn events
	m_renderQueue.clear();

	if(!isBlend)
	{
		glDisable(GL_BLEND);
	}
}