/****************************************************************************
** Sami meta object code from reading C++ file 'sami.h'
**
** Created: Thu Feb 10 21:13:50 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.3   edited Aug 5 16:40 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "sami.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Sami::className() const
{
    return "Sami";
}

QMetaObject *Sami::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Sami( "Sami", &Sami::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Sami::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Sami", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Sami::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Sami", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Sami::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Sami", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Sami.setMetaObject( metaObj );
    return metaObj;
}

void* Sami::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Sami" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool Sami::qt_invoke( int _id, QUObject* _o )
{
    return QMainWindow::qt_invoke(_id,_o);
}

bool Sami::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Sami::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool Sami::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
