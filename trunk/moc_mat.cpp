/****************************************************************************
** Mat meta object code from reading C++ file 'mat.h'
**
** Created: Thu Feb 10 21:13:46 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.3   edited Aug 5 16:40 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mat.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Mat::className() const
{
    return "Mat";
}

QMetaObject *Mat::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Mat( "Mat", &Mat::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Mat::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Mat", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Mat::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Mat", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Mat::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Mat", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Mat.setMetaObject( metaObj );
    return metaObj;
}

void* Mat::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Mat" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool Mat::qt_invoke( int _id, QUObject* _o )
{
    return QMainWindow::qt_invoke(_id,_o);
}

bool Mat::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Mat::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool Mat::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
