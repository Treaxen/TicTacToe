#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(const std::string & file)
{
	glGenTextures(TEXTURE_COUNT, &mTextureID);

	//load file and decode image
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, file);

	m_width = width;
	m_height = height;

	//If there's an error, display it
	if (error != 0)
	{
		std::cout << "png load error :" << error << " : " << lodepng_error_text(error) << std::endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //apply texture wrapping along horizontal part
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //apply texture wrapping along vertical part

																  //bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //near filtering (for when texture needs to be scaled up)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //near filtering (for when texture needs to be scaled down)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
}

Sprite::~Sprite()
{
}

void Sprite::draw(float x, float y, float scale, float rotation, Color color, enumBlend blendMode)
{
	glEnable(GL_BLEND);
	
	if (blendMode == enumBlend::alpha)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	else if (blendMode == enumBlend::additive)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	else if (blendMode == enumBlend::multiply)
		glBlendFunc(GL_DST_COLOR, GL_ZERO);

	glEnable(GL_ALPHA_TEST);

	glColor4f(color.r, color.g,color.b, color.a);

	float halfWidth = (m_width / 2) * scale;
	float halfHeight = (m_height / 2) * scale;
	
	rotation = rotation * M_PI / 180;

	//Bottom Left
	float x1 = (-halfHeight * sin(rotation)) + (-halfWidth * cos(rotation)); 
	float y1 = (-halfHeight * cos(rotation)) - (-halfWidth * sin(rotation));

	//Top Left
	float x2 = ( halfHeight * sin(rotation)) + (-halfWidth * cos(rotation)); 
	float y2 = ( halfHeight * cos(rotation)) - (-halfWidth * sin(rotation));

	//Bottom Right
	float x3 = (-halfHeight * sin(rotation)) + ( halfWidth * cos(rotation));
	float y3 = (-halfHeight * cos(rotation)) - ( halfWidth * sin(rotation));

	//Top Right
	float x4 = ( halfHeight * sin(rotation)) + ( halfWidth * cos(rotation));
	float y4 = ( halfHeight * cos(rotation)) - ( halfWidth * sin(rotation));
	
	//glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D); //enable texturing
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1 + x, y1 + y, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2 + x, y2 + y, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x3 + x, y3 + y, 0.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(x3 + x, y3 + y, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x4 + x, y4 + y, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x2 + x, y2 + y, 0.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
