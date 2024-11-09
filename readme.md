
---
***NOTE:***
- *Most objects should be declared globally and dynamically to avoid unintended deletion of objects.*

>`ArrayBuffer  *buffer;`
>
>`IndexBuffer  *ibuffer;`
>
>`DrawableObj  *obj;`
>
>`AttribFormat  *attribFormat;`

- Ensure GL_VERTEX_ARRAY and GL_COLOR_ARRAY is enabled on client state.

---  

To use the DrawableObj class, you must first specify the vertex format/s of your vertex file/s.

You can achieve this by:

>`attribFormat = new AttribFormat();`
>
>`attribFormat->addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);`
>
>`attribFormat->addAttrib<GLubyte>(3, GL_COLOR_ARRAY);`

- The template parameter will specify the data type of the vertex attribute.
- First method parameter is the number of components.
- Second method parameter is the attribute name.
-- (Only vertex arrays and color arrays are supported as of now.)
- The whole attribFormat object represents a format of a buffer and can be reused.

---
An ArrayBuffer is then needed to obtain vertex data. The attribute format declared earlier must be passed to parse the file given.

>`buffer = new ArrayBuffer("vertices.data", attribFormat);`

An IndexBuffer is optional; only if wanted. All indices will use the GLuint data type.

>`ibuffer  =  new  IndexBuffer("indices.data");`

---
To declare a DrawableObj, you must specify the mode and vertex data (ArrayBuffer).

>`obj  =  new  DrawableObj(GL_QUADS,  buffer);`

You can also specify an index buffer either by adding the line:

>`obj->setIndexBuffer(ibuffer);`

or by changing the constructor to:

>`obj  =  new  DrawableObj(GL_QUADS,  buffer,  ibuffer);`

To draw the object, simply call:

>`obj->draw();`

*\*Users must call glFlush() after to see the object.\**