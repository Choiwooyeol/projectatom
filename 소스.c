#pragma warning(disable:4996)
#include <stdio.h>
#include<math.h>
#include <glaux.h>
#include <glut.h> 
#define MAX_LIGHT_POSITION 30.00
#define RINGS_ON 0
#define RINGS_OFF 1
#define EXPLAIN_ON 0
#define EXPLAIN_OFF 1

GLfloat mat_shininess[] = { 70.0 };
GLfloat light_position[] = { -30.0, 0.0, -30.0, 0.0 };
GLfloat light_position1[] = { -30.0, 0.0, 0.0, 0.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat lightintensity[] = { 0.7,0.7,0.7,1.0 };

GLfloat AmbientColor[] = { 0.4f, 0.4f,0.4f, 0.0f };
GLfloat DiffuseColor[] = { 0.3f, 0.3f, 0.3f, 0.0f };
GLfloat SpecularColor[] = { 0.3f, 0.3f, 0.3f, 0.0f };

float colors[][3] = { { 1,0,0 },{ 0,1,0 },{ 0,0,1 },{ 1,1,0 } ,{ 0,1,1 },{ 0.5,1,0.25 },{ 1,1,1 },{ 1,0,0 },{ 0.2,0.2,0.9 },{ 0.75,0,0 } };
float color[][3] = { { 0,0.7,0 },{ 0.8,0.8,0 },{0.8,0.5,0 },{ 0,0,0.9 } ,{ 0,0.3,0 },{ 0,0.5,0.5 }, {0.8,1,1} };
float rottor[][3] = { { 1,0,0 },{ 0,1,0 },{ -1,1,0 },{ 1,1,0 },{ 1,0,0 },{ 0,1,0 },{ -1,1,0 },{ 1,1,0 },{ 1,0,0 },{ 0,1,0 },{ -1,1,0 },{ 1,1,0 },{ 1,0,0 },{ 0,1,0 },{ -1,1,0 },{ 1,1,0 },{ 1,0,0 },{ 0,1,0 },{ -1,1,0 },{ 1,1,0 } };
float torsize[] = { 4, 4.5, 5, 5.5, 6, 6.5, 6,6, 6 ,6, 6,6,6,6,6,6,6,6,6,6,6 };
float rot[][3] = { { 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ -1,1,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ -1,1,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ -1,1,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ -1,1,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },{ -1,1,0 } };
float ele[][3] = { { 4,0,0 },{ 0,4.5,0 },{ -2.8868,2.8868,2.8868 },{ 3.1755,3.1755,3.1755 },{ 6,0,0 },{ 0,6.5,0 },{ -4.0415,4.0415,4.0415 },{ 4.3301,4.3301,4.3301 },{ 6.5,0,0 },{ 0,5.5,0 },{ -3,3,3 },{ 3.8,3.8,3.8 },{ 7,0,0 },{ 0,7,0 },{ -3.3,3.3,3.3 },{ 4,4,4 },{ 7,0,0 },{ 0,4.5,0 },{ -3.3333,3.3333,3.3333 },{ 4,4,4 }, };
float axisa[] = { 0.5,1.0,1.5,2,2.5,3,3.5,4,4.5, 5, 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 };
float axis[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

// 카메라 방향앵글
float angle = 0.0f;

// 실제 카메라 방향 벡터
float lx = 0.0f, lz = -1.0f;

// 카메라의 x,z위치
float x = 0.0f, z = 5.0f;

// 키상태 // 0
//처리중에 키가 0일때
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

int imageswitch = 0;
int w, h;
int ringflag = 1;
int explainflag = 1;
int n = 0; //전자 갯수
int xlight = 2, ylight = 2, zlight = 2;
rotx, roty = 0; //회전 처리

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수

GLuint textures[20];

////////////////////////////////////////////////
/* FONT*/
char s[50];
void *font = GLUT_STROKE_ROMAN;

void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	char *string) {

	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();

	gluOrtho2D(0, w, h, 0);

	glMatrixMode(GL_MODELVIEW);
}

void PrintString(char* string, int x, int y) // 문자열출력
{
	sprintf(s, string);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	renderBitmapString(x, y, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	restorePerspectiveProjection();
}

void PrintAtom2()
{
	PrintString("Not metal", 57, 895);
	PrintString("Alcaline E", 160, 895);
	PrintString(" Alcaline", 260, 895);
	PrintString("Noble gas", 358, 895);
	PrintString("Metalloid", 469, 895);
	PrintString("Post-transition", 570, 895);
}
void PrintAtom(int num) // 설명을 넣으면됨.
{
	if (num == 1)
	{
		PrintString("H - Hydrogen - 1", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It means the material of water", 400, 645);
	}
	if (num == 2)
	{
		PrintString("He - Helium - 2", 400, 600);
		PrintString("Noble gas", 400, 630);
		PrintString("It means the reactivity is low", 400, 645);
	}
	if (num == 3)
	{
		PrintString("Li - Lithium - 3", 400, 600);
		PrintString("Alkali metal", 400, 630);
		PrintString("It means the Lightest solid", 400, 645);
	}
	if (num == 4)
	{
		PrintString("Be - Beryllium - 4", 400, 600);
		PrintString("Alkaline earth metal", 400, 630);
		PrintString("It has the High thermal conductivity", 400, 645);
	}
	if (num == 5)
	{
		PrintString("B - Boron - 5", 400, 600);
		PrintString("Metalloid", 400, 630);
		PrintString("It is Hard next to diamond", 400, 645);
	}
	if (num == 6)
	{
		PrintString("C - Carbon - 6", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It is used to make black smoke", 400, 645);
		PrintString("or diamonds ", 400, 660);
	}
	if (num == 7)
	{
		PrintString("N - Nitrogen - 7", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It can react with hydrogen", 400, 645);
		PrintString("to produce ammonia.", 400, 660);
	}
	if (num == 8)
	{
		PrintString("O - Oxygen - 8", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It is substance essential to life for humans,", 400, 645);
	}
	if (num == 9)
	{
		PrintString("F - Fluorine - 9", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It means the most powerful oxidizer", 400, 645);
	}
	if (num == 10)
	{
		PrintString("Ne - Neon - 10", 400, 600);
		PrintString("Noble gas", 400, 630);
		PrintString("It has no color, smell, taste" ,400, 645);
		PrintString("and is lighter than air.", 400, 660);
	}
	if (num == 11)
	{
		PrintString("Na - Natrium - 11", 400, 600);
		PrintString("Alkali metal", 400, 630);
		PrintString("It has very strong reactivity.", 400, 645);
	}
	if (num == 12)
	{
		PrintString("Mg - Magnesium - 12", 400, 600);
		PrintString("Alkaline earth metal", 400, 630);
		PrintString("It is Harder than low density", 400, 645);
	}
	if (num == 13)
	{
		PrintString("Al - Aluminium - 13", 400, 600);
		PrintString("Post-transition meta", 400, 630);
		PrintString("It is rich in malleability and ductility.", 400, 645);
	}
	if (num == 14)
	{
		PrintString("Si - Silicon - 14", 400, 600);
		PrintString("Metalloid", 400, 630);
		PrintString("It shows the properties of", 400, 645);
		PrintString("semiconductor", 400, 660);
	}
	if (num == 15)
	{
		PrintString("P - Phosphorus - 15", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It has properties similar to graphite.", 400, 645);
	}
	if (num == 16)
	{
		PrintString("S - Sulfur - 16", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It is essential for life, ", 400, 645);
		PrintString("amino acids contain sulfur.", 400, 660);
	}
	if (num == 17)
	{
		PrintString("Cl - Chlorine - 17", 400, 600);
		PrintString("Not metal", 400, 630);
		PrintString("It has the highest electron affinity,", 400, 645);
		PrintString("among the elements,", 400, 660);
	}
	if (num == 18)
	{
		PrintString("Ar - Argon - 18", 400, 600);
		PrintString("Noble gas", 400, 630);
		PrintString("It is most common Inactive gases", 400, 645);
		PrintString("on earth.", 400, 660);
	}
	if (num == 19)
	{
		PrintString("K - Kalium - 19", 400, 600);
		PrintString("Alkaline metal", 400, 630);
		PrintString("It rapidly reacts in the air or water", 400, 645);
		PrintString("to oxidize.", 400, 645);
	}
	if (num == 20)
	{
		PrintString("Ca - Calcium  - 20", 400, 600);
		PrintString("Alkaline earth metal", 400, 630);
		PrintString("It is essential for bone", 400, 645);
		PrintString("and its growth and maintenance.", 400, 660);
	}
	
}
//////////////////////////////////////////////////FONT END

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;

}

void rotatelight()
{
	if (xlight % 3 == 0)
	{
		if (light_position[0] > -MAX_LIGHT_POSITION)
			light_position[0] -= 0.2;
		else
			xlight++;
	}
	else if (xlight % 3 == 1)
	{
		if (light_position[0] < 30.00)
			light_position[0] += 0.2;
		else
			xlight--;
	}

	if (ylight % 3 == 0)
	{
		if (light_position[1] > -MAX_LIGHT_POSITION)
			light_position[1] -= 0.2;
		else
			ylight++;
	}
	else if (ylight % 3 == 1)
	{
		if (light_position[1] < MAX_LIGHT_POSITION)
			light_position[1] += 0.2;
		else
			ylight--;
	}

	if (zlight % 3 == 0)
	{
		if (light_position[2] > -MAX_LIGHT_POSITION)
			light_position[2] -= 0.2;
		else
			zlight++;
	}
	else if (zlight % 3 == 1)
	{
		if (light_position[2] < MAX_LIGHT_POSITION)
			light_position[2] += 0.2;
		else
			zlight--;
	}

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position1);
}

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);  // 은면 제거
	glFrontFace(GL_CCW);   // 앞면 설정  
	glEnable(GL_CULL_FACE);  // 내부는 잘라낸다  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 배경색 설정
}

void changeSize(int ww, int hh) {

	w = ww;
	h = hh;

	// 0으로 나뉘는걸 방지하기위해
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	//직사투영
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	//모델뷰 다시 변경
	glMatrixMode(GL_MODELVIEW);
}


void LoadIMG()
{
	glGenTextures(20, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	pBytes = LoadDIBitmap("1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	pBytes = LoadDIBitmap("2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	pBytes = LoadDIBitmap("3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	pBytes = LoadDIBitmap("4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	pBytes = LoadDIBitmap("5.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	pBytes = LoadDIBitmap("6.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	pBytes = LoadDIBitmap("7.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	pBytes = LoadDIBitmap("8.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	pBytes = LoadDIBitmap("9.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[9]);
	pBytes = LoadDIBitmap("10.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[10]);
	pBytes = LoadDIBitmap("11.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[11]);
	pBytes = LoadDIBitmap("12.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[12]);
	pBytes = LoadDIBitmap("13.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[13]);
	pBytes = LoadDIBitmap("14.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[14]);
	pBytes = LoadDIBitmap("15.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[15]);
	pBytes = LoadDIBitmap("16.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[16]);
	pBytes = LoadDIBitmap("17.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[17]);
	pBytes = LoadDIBitmap("18.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[18]);
	pBytes = LoadDIBitmap("19.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[19]);
	pBytes = LoadDIBitmap("20.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

}

void strokeString(float x, float y, float sx, float sy, char *string, int width)
{
	char *c;
	glLineWidth(width);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(sx, sy, 0);
	for (c = string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void sphere(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();
}

void nucleus()
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	//glTranslatef(0, 0, -10);
	glutSolidSphere(0.75, 50, 50);

	if (n == 1 || n == 6 || n == 7 || n == 8 || n == 9|| n == 15 || n == 16 || n == 17)
	{
		glColor3fv(color[0]);
	}
	else if (n == 2 || n == 10 || n == 18)
	{
		glColor3fv(color[3]);
	}
	else if (n == 3 || n == 11 || n == 19)
	{
		glColor3fv(color[2]);
	}
	else if (n == 4 || n == 12)
	{
		glColor3fv(color[1]);
	}
	else if (n == 20)
	{
		glColor3fv(color[2]);
	}
	else if(n == 13)
	{
		glColor3fv(color[5]);
	}
	else if (n == 5 || n == 14)
	{
		glColor3fv(color[4]);
	}
	else glColor3f(0.5,0.6, 0.6);
		

	sphere(-1.5, 0, 0);
	sphere(1.5, 0, 0);
	sphere(0, 1.5, 0);
	sphere(0, -1.5, 0);
	sphere(0, 0, -1.5);
	sphere(0, 0, 1.5);

	sphere(2.25, 0, 0);
	sphere(0, 0, 2.25);
	sphere(0, 0, -2.25);
	sphere(-2.25, 0, 0);
	sphere(0, 2, 0);
	sphere(0, -2, 0);

	
	sphere(-1.5, -1.5, 0);
	sphere(1.5, 1.5, 0);
	sphere(-1.5, 1.5, 0);
	sphere(1.5, -1.5, 0);

	
	sphere(-1.5, 0, 1.5);
	sphere(1.5, 0, 1.5);
	sphere(0, 1.5, 1.5);
	sphere(0, -1.5, 1.5);

	sphere(-1.5, 0, -1.5);
	sphere(1.5, 0, -1.5);
	sphere(0, 1.5, -1.5);
	sphere(0, -1.5, -1.5);
	glPopMatrix();
}

void electrons(float ele[], int i)
{
	glColor3f(0.5,0.5,0.5);
	if (ringflag)
	{
		glPushMatrix();
		glRotatef(90, rottor[i][0], rottor[i][1], rottor[i][2]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
		glutSolidTorus(0.03, torsize[i] + 0.03, 10, 100);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glPopMatrix();
	}
	glPushMatrix();
	glColor3fv(color[6]);
	glTranslatef(ele[0], ele[1], ele[2]);
	glutSolidSphere(0.3, 50, 50);
	glPopMatrix();
}

void renderScene(void) {

	int i;

	// 색,깊이 버퍼 초기화
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glShadeModel(GL_SMOOTH);
	rotatelight();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientColor);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseColor);
	glLightfv(GL_LIGHT2, GL_POSITION, SpecularColor);
	glEnable(GL_COLOR_MATERIAL);

	// 위치 초기화
	glLoadIdentity();
	// 카메라 설정
	gluLookAt(x, 1.0f, 20.0,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	//렌더링 불러오기
	if (imageswitch == 0)
	{
		LoadIMG();
		imageswitch++;
	}
	rotatelight();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-4.5f, 9.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-5.5f, 9.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-5.5f, 8.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(-4.5f, 8.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	//glColor3f(0.9f, 0.9f, 0.9f);
	glTexCoord2f(1, 1);
	glVertex3f(5.5f, 9.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(4.5f, 9.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(4.5f, 8.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(5.5f, 8.0f, 0.0f);
	glEnd();

	for (i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i + 2]);
		glBegin(GL_QUADS);
		//glColor3f(0.9f, 0.9f, 0.9f);
		glTexCoord2f(1, 1);
		glVertex3f(-4.5f + i * 1.1, 7.9f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-5.5f + i * 1.1, 7.9f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-5.5f + i * 1.1, 6.9f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(-4.5f + i * 1.1, 6.9f, 0.0f);
		glEnd();
	}

	for (i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i + 10]);
		glBegin(GL_QUADS);
		//glColor3f(0.9f, 0.9f, 0.9f);
		glTexCoord2f(1, 1);
		glVertex3f(-4.5f + i * 1.1, 6.8f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-5.5f + i * 1.1, 6.8f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-5.5f + i * 1.1, 5.8f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(-4.5f + i * 1.1, 5.8f, 0.0f);
		glEnd();
	}

	for (i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i + 18]);
		glBegin(GL_QUADS);
		//glColor3f(0.9f, 0.9f, 0.9f);
		glTexCoord2f(1, 1);
		glVertex3f(-4.5f + i * 1.1, 5.7f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-5.5f + i * 1.1, 5.7f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-5.5f + i * 1.1, 4.7f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(-4.5f + i * 1.1, 4.7f, 0.0f);
		glEnd();
	}

	for (i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i + 4]);
		glBegin(GL_QUADS);
		//glColor3f(0.9f, 0.9f, 0.9f);
		glTexCoord2f(1, 1);
		glVertex3f(0.0f + i * 1.1, 7.9f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0f + i * 1.1, 7.9f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1.0f + i * 1.1, 6.9f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(0.0f + i * 1.1, 6.9f, 0.0f);
		glEnd();
	}

	for (i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i + 12]);
		glBegin(GL_QUADS);
		//glColor3f(0.9f, 0.9f, 0.9f);
		glTexCoord2f(1, 1);
		glVertex3f(0.0f + i * 1.1, 6.8f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0f + i * 1.1, 6.8f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1.0f + i * 1.1, 5.8f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(0.0f + i * 1.1, 5.8f, 0.0f);
		glEnd();
	}

	for (i = 0; i < 6; i++)
	{
		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3fv(color[i]); // 준금속
		if (i == 3)
		{
			glVertex3f(-4.9f + i * 1.65, -5.27f, 0.0f);
			glVertex3f(-5.2f + i * 1.65, -5.27f, 0.0f);
			glVertex3f(-5.2f + i * 1.65, -5.6f, 0.0f);
			glVertex3f(-4.9f + i * 1.65, -5.6f, 0.0f);
		}
		else {
			glVertex3f(-4.9f + i * 1.7, -5.3f, 0.0f);
			glVertex3f(-5.2f + i * 1.7, -5.3f, 0.0f);
			glVertex3f(-5.2f + i * 1.7, -5.6f, 0.0f);
			glVertex3f(-4.9f + i * 1.7, -5.6f, 0.0f);
		}
		glEnd();
		glPopMatrix();
	}
	glPushMatrix();
	glTranslated(0, 0, -10);
	glRotatef(roty, 0.0, 1.0, 0.0);
	glRotatef(rotx, 1.0, 0.0, 0.0);
	nucleus();

	for (i = 0; i < n; i++)
	{
		glPushMatrix();
		//glTranslatef(0, 0, -10);
		glRotatef((axis[i] += axisa[i]), rot[i][0], rot[i][1], rot[i][2]);
		//if (scaleflag == 2)
		//glScalef(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);
		electrons(ele[i], i);
		glPopMatrix();
		if (axis[i] >= 360) axis[i] -= 360.0;
	}
	PrintAtom2();

	glPopMatrix();
	if(explainflag == 1)
	PrintAtom(n);
	glutSwapBuffers();

}

int pick(int x, int y)  //메뉴 선택을 위한 함수. 선택한 기능을 리턴함
{

	if (y <= 79 && y >= 17) //첫째줄
	{
		if (x >= 18 && x <= 76) //H
		{
			return 1;
		}
		if (x >= 622 && x <= 681) //He
		{
			return 2;
		}
	}

	if (y <= 145 && y >= 84) //두번째줄
	{
		if (x >= 18 && x <= 76) //Li
		{
			return 3;
		}
		if (x >= 82 && x <= 145) //Be
		{
			return 4;
		}
		if (x >= 290 && x <= 350) //B
		{
			return 5;
		}
		if (x >= 356 && x <= 416) // C
		{
			return 6;
		}
		if (x >= 422 && x <= 483) // N
		{
			return 7;
		}
		if (x >= 488 && x <= 547) // O
		{
			return 8;
		}
		if (x >= 554 && x <= 613) // F
		{
			return 9;
		}
		if (x >= 622 && x <= 680) //Ne
		{
			return 10;
		}
	}

	if (y <= 210 && y >= 150) //3번째줄
	{
		if (x >= 18 && x <= 76) //Na
		{
			return 11;
		}
		if (x >= 82 && x <= 145) //Mg
		{
			return 12;
		}
		if (x >= 290 && x <= 350) //Al
		{
			return 13;
		}
		if (x >= 356 && x <= 416) //Si
		{
			return 14;
		}
		if (x >= 422 && x <= 483) //P
		{
			return 15;
		}
		if (x >= 488 && x <= 547) //S
		{
			return 16;
		}
		if (x >= 554 && x <= 613) //Cl
		{
			return 17;
		}
		if (x >= 622 && x <= 680) //Ar
		{
			return 18;
		}
	}

	if (y <= 274 && y >= 217) //네번째 줄
	{
		if (x >= 18 && x <= 76) //K
		{
			return 19;
		}
		if (x >= 82 && x <= 145) //Ca
		{
			return 20;
		}
	}
	else return 0;
}

void mouseButton(int button, int state, int x, int y) {
	// 모션 레프트버튼눌렸을때
	int atom;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		atom = pick(x, y);
		switch (atom)
		{
		case 1:
			n = 1;
			break;
		case 2:
			n = 2;
			break;
		case 3:
			n = 3;
			break;
		case 4:
			n = 4;
			break;
		case 5:
			n = 5;
			break;
		case 6:
			n = 6;
			break;
		case 7:
			n = 7;
			break;
		case 8:
			n = 8;
			break;
		case 9:
			n = 9;
			break;
		case 10:
			n = 10;
			break;
		case 11:
			n = 11;
			break;
		case 12:
			n = 12;
			break;
		case 13:
			n = 13;
			break;
		case 14:
			n = 14;
			break;
		case 15:
			n = 15;
			break;
		case 16:
			n = 16;
			break;
		case 17:
			n = 17;
			break;
		case 18:
			n = 18;
			break;
		case 19:
			n = 19;
			break;
		case 20:
			n = 20;
			break;
		}
	}
}

void myinit()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
	glEnable(GL_COLOR_MATERIAL);
}

////////////////Menu///////////////
void processMainMenu2(int option)
{

}

void processRings(int option)
{
	if (option == RINGS_ON)   ringflag = 1;
	else ringflag = 0;
}

void processExplain(int option)
{
	if (option == EXPLAIN_ON)   explainflag = 1;
	else explainflag = 0;
}

void createGLUTMenus() ////////menu
{
	//   int i;
	int menuRings = glutCreateMenu(processRings);
	glutAddMenuEntry("On", RINGS_ON);
	glutAddMenuEntry("Off", RINGS_OFF);
	int menuExplain = glutCreateMenu(processExplain);
	glutAddMenuEntry("On", EXPLAIN_ON);
	glutAddMenuEntry("Off", EXPLAIN_OFF);
	glutCreateMenu(processMainMenu2);
	glutAddSubMenu("Rings", menuRings);
	glutAddSubMenu("Explan text", menuExplain);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	///////////////////////////////Menu End
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W': rotx--;
		break;
	case 's':
	case 'S':   rotx++;
		break;
	case 'a':
	case 'A':   roty--;
		break;
	case 'd':
	case 'D':   roty++;
		break;
	}
}

void keyboard2(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 13:
		myinit();
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);glutInitWindowPosition(100, 100);
		glutInitWindowSize(700, 1000);
		glutCreateWindow("Atom");
		glutDisplayFunc(renderScene);
		createGLUTMenus();
		glutReshapeFunc(changeSize);
		glutIdleFunc(renderScene);
		glutMouseFunc(mouseButton);
		glutKeyboardFunc(keyboard);
		glutMainLoop();
		break;
	}
	glutPostRedisplay();
}

void first()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	strokeString(300, 670, 0.3, 0.3, "COMPUTER GRAPHICS", 4);
	strokeString(335, 500, 0.3, 0.3, "FINAL PROJECT", 2);
	glColor3f(0, 0.5, 1);
	strokeString(75, 420, 0.4, 0.4, "SIMULATION OF PERIODIC TABLE", 6);
	glColor3f(0, 0.5, 1);
	glColor3f(0, 0.5, 1);
	strokeString(650, 230, 0.15, 0.15, "By:", 2);
	glColor3f(0, 0.5, 1);
	strokeString(650, 110, 0.18, 0.18, "CHOI WOOYEOL", 2);
	strokeString(650, 170, 0.18, 0.18, "JIN HYEONTAK", 2);
	glColor3f(1, 0, 0);
	strokeString(650, 140, 0.18, 0.18, "2013041023", 2);
	strokeString(650, 200, 0.18, 0.18, "2013080021 ", 2);
	glColor3f(0.5, 0, 0);
	strokeString(265, 750, 0.5, 0.5, "PRESS ENTER", 6);
	glutSwapBuffers();
}

void initfirst()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1000, 0, 1000, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {

	//window 초기화

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 1000);
	glutCreateWindow("Atom");

	initfirst();
	glutDisplayFunc(first);


	glutKeyboardFunc(keyboard2);
	glutMainLoop();

	return EXIT_SUCCESS;

}