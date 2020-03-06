#include <cstring>

using namespace std;

GLuint textura1, textura2, chao, parede, espada;

struct Ponto{
	float x;
	float y;
	float z;
};

struct Textura{
	float x;
	float y;
};

void carregaOBJ(const char *path, vector<Ponto> &vertices, vector<Textura> &texturasVertice, vector<Ponto> &normaisVertice){
	char lido[100];
	Ponto temp_ponto;
	Ponto temp_normal;
	Textura temp_textura;
	vector<Ponto> pontos;
	vector<Ponto> normais;
	vector<Textura> texturas;
	printf("Carregando Arquivo OBJ %s...\n", path);
	FILE * file = fopen(path, "r");
	if(file == NULL){
		printf("Não foi possivel abrir o arquivo obj %s!\n", path);
		return;
	}
	
	while(fscanf(file, "%s", lido) != EOF){
		if(strcmp(lido, "v") == 0){
            fscanf(file, "%f %f %f\n", &temp_ponto.x, &temp_ponto.y, &temp_ponto.z);
			pontos.push_back(temp_ponto);
        }
        if(strcmp(lido, "vt") == 0){
            fscanf(file, "%f %f\n", &temp_textura.x, &temp_textura.y);
			texturas.push_back(temp_textura);
        }
        if(strcmp(lido, "vn") == 0){
            fscanf(file, "%f %f %f\n", &temp_normal.x, &temp_normal.y, &temp_normal.z);
			normais.push_back(temp_normal);
        }
        if(strcmp(lido, "f") == 0){
            int p1, p2, p3, p4, p5, p6, p7, p8, p9;
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &p1, &p4, &p7, &p2, &p5, &p8, &p3, &p6, &p9);
            
            vertices.push_back(pontos[p1-1]);
            vertices.push_back(pontos[p2-1]);
            vertices.push_back(pontos[p3-1]);
            
            texturasVertice.push_back(texturas[p4-1]);
            texturasVertice.push_back(texturas[p5-1]);
            texturasVertice.push_back(texturas[p6-1]);
            
            normaisVertice.push_back(normais[p7-1]);
            normaisVertice.push_back(normais[p8-1]);
            normaisVertice.push_back(normais[p9-1]);
        }
	}
	fclose(file);
	fprintf(stderr, "Arquivo OBJ %s carregado.\n", path);
}

GLuint carregaBMP(const char * imagepath){
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;
	
	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file){
		printf("Image could not be opened\n"); 
		return 0;
	}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0) dataPos=54; // The BMP header is done that way
	
	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	//Everything is in memory now, the file can be closed
	fclose(file);
	
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	fprintf(stderr, "Textura %s Carregada.\n", imagepath);
	return textureID;
}

void desenhaVetorTextura(vector<Ponto> &vertices, vector<Textura> &texturas, vector<Ponto> &normais, GLuint textura){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);
	for(vector<Ponto>::size_type i = 0; i<vertices.size(); i+=3){
        glBegin(GL_TRIANGLES);
			glTexCoord2f(texturas[i].x, texturas[i].y);
			glNormal3f(normais[i].x, normais[i].y, normais[i].z);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			glTexCoord2f(texturas[i+1].x, texturas[i+1].y);
			glNormal3f(normais[i+1].x, normais[i+1].y, normais[i+1].z);
			glVertex3f(vertices[i+1].x, vertices[i+1].y, vertices[i+1].z);
			glTexCoord2f(texturas[i+2].x, texturas[i+2].y);
			glNormal3f(normais[i+2].x, normais[i+2].y, normais[i+2].z);
			glVertex3f(vertices[i+2].x, vertices[i+2].y, vertices[i+2].z);
        glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}
