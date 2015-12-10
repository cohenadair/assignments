// glQuaternion.h: interface for the glQuaternion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLQUATERNION_H__52FB84BB_6D1B_4314_833F_5A8737A35DAB__INCLUDED_)
#define AFX_GLQUATERNION_H__52FB84BB_6D1B_4314_833F_5A8737A35DAB__INCLUDED_

#include <SDL2/SDL_opengl.h>			// Header File For The OpenGL32 Library

#include <math.h>

#define PI			3.14159265358979323846

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class glQuaternion
{
public:
    glQuaternion operator *(glQuaternion q);
    void CreateMatrix(GLfloat *pMatrix);
    void CreateFromAxisAngle(GLfloat x, GLfloat y, GLfloat z, GLfloat degrees);
    void getAxisAngle(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &degrees);
    glQuaternion();
    virtual ~glQuaternion();
    void Normalize ();
private:
    GLfloat m_w;
    GLfloat m_z;
    GLfloat m_y;
    GLfloat m_x;
};

#endif // !defined(AFX_GLQUATERNION_H__52FB84BB_6D1B_4314_833F_5A8737A35DAB__INCLUDED_)