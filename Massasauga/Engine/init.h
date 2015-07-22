#ifndef INIT_H
#define INIT_H

class Init
{
public:
	Init();

private:
	Init(const Init &); // disallow copy constructor
	Init & operator=(const Init &); // disallow assignment operator
	bool InitOpenGL();
#if defined ( _DEBUG )
	void DebugOpenGL();
#endif
};
#endif