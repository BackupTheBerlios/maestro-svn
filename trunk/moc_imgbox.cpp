/****************************************************************************
** ImageBox meta object code from reading C++ file 'imgbox.h'
**
** Created: Mon Feb 14 23:32:29 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.3   edited Aug 5 16:40 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "imgbox.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ImageBox::className() const
{
    return "ImageBox";
}

QMetaObject *ImageBox::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ImageBox( "ImageBox", &ImageBox::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ImageBox::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ImageBox", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ImageBox::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ImageBox", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ImageBox::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGroupBox::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"ImageBox", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ImageBox.setMetaObject( metaObj );
    return metaObj;
}

void* ImageBox::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ImageBox" ) )
	return this;
    return QGroupBox::qt_cast( clname );
}

bool ImageBox::qt_invoke( int _id, QUObject* _o )
{
    return QGroupBox::qt_invoke(_id,_o);
}

bool ImageBox::qt_emit( int _id, QUObject* _o )
{
    return QGroupBox::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ImageBox::qt_property( int id, int f, QVariant* v)
{
    return QGroupBox::qt_property( id, f, v);
}

bool ImageBox::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
