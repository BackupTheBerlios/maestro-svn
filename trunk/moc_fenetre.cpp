/****************************************************************************
** Fenetre meta object code from reading C++ file 'fenetre.h'
**
** Created: Mon Feb 14 23:32:27 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.3   edited Aug 5 16:40 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "fenetre.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Fenetre::className() const
{
    return "Fenetre";
}

QMetaObject *Fenetre::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Fenetre( "Fenetre", &Fenetre::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Fenetre::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Fenetre", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Fenetre::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Fenetre", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Fenetre::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"OuvrirImage", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "OuvrirImage()", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Fenetre", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Fenetre.setMetaObject( metaObj );
    return metaObj;
}

void* Fenetre::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Fenetre" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool Fenetre::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: OuvrirImage(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Fenetre::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Fenetre::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool Fenetre::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
