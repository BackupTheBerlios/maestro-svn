/****************************************************************************
** Romain meta object code from reading C++ file 'romain.h'
**
** Created: Thu Feb 10 21:13:48 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.3   edited Aug 5 16:40 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "romain.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Romain::className() const
{
    return "Romain";
}

QMetaObject *Romain::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Romain( "Romain", &Romain::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Romain::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Romain", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Romain::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Romain", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Romain::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Romain", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Romain.setMetaObject( metaObj );
    return metaObj;
}

void* Romain::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Romain" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool Romain::qt_invoke( int _id, QUObject* _o )
{
    return QMainWindow::qt_invoke(_id,_o);
}

bool Romain::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Romain::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool Romain::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
