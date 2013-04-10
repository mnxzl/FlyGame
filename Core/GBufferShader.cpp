#include "GBufferShader.h"

GBufferShader::GBufferShader()
{

}

void GBufferShader::draw(SHADER_PARAMETER_DATA& wMatrixData)
{
	int indexC = 0;
	this->shader->Render();
	//drawData.cMatrixBuffer->setBuffer();

	for( int i = 0; i< this->drawData.size();i++)
	{
		cBufferMatrix* cb = (cBufferMatrix*)wMatrixData.cMatrixBuffer->Map();
		if(cb)
		{
			cb->world = *this->drawData[i].worldMatrix; // add the world matrix of the object
			wMatrixData.cMatrixBuffer->Unmap();
		}

		wMatrixData.cMatrixBuffer->setBuffer();
		for(int k = 0; k <this->drawData[i].buffers.size(); k++)
		{
			this->drawData[i].buffers[k]->setBuffer(0);

			if(this->drawData[i].buffers[k]->getType() == BUFFER_FLAG::TYPE_INDEX_BUFFER)
				indexC = this->drawData[i].buffers[k]->getNrOfElements();
		}
		this->shader->GetDeviceContext()->DrawIndexed(indexC, 0, 0);
	}
}