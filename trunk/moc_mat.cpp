/****************************************************************************
** Mat meta object code from reading C++ file 'mat.h'
**
** Created: Mon Feb 14 23:32:31 2005
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
    static const QUMethod slot_0 = {"ChargerImage", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "img", &static_QUType_varptr, "\x0f", QUParameter::In }
    };
    static const QUMethod slot_1 = {"Filtre", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "img", &static_QUType_varptr, "\x0f", QUParameter::In }
    };
    static const QUMethod slot_2 = {"Reconnaissance", 1, param_slot_2 };
    static const QUMethod slot_3 = {"Reconnaitre", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "p", &static_QUType_ptr, "p_liste", QUParameter::In },
	{ "img", &static_QUType_varptr, "\x0f", QUParameter::In }
    };
    static const QUMethod slot_4 = {"AfficherLignes", 2, param_slot_4 };
    static const QUMethod slot_5 = {"BoutonLigne", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ "img", &static_QUType_varptr, "\x0f", QUParameter::In }
    };
    static const QUMethod slot_6 = {"Filtre2", 1, param_slot_6 };
    static const QUMethod slot_7 = {"BoutonFiltre", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ "i", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"slider1_valueChanged", 1, param_slot_8 };
    static const QMetaData slot_tbl[] = {
	{ "ChargerImage()", &slot_0, QMetaData::Public },
	{ "Filtre(QImage*)", &slot_1, QMetaData::Public },
	{ "Reconnaissance(QImage*)", &slot_2, QMetaData::Public },
	{ "Reconnaitre()", &slot_3, QMetaData::Public },
	{ "AfficherLignes(p_liste,QImage*)", &slot_4, QMetaData::Public },
	{ "BoutonLigne()", &slot_5, QMetaData::Public },
	{ "Filtre2(QImage*)", &slot_6, QMetaData::Public },
	{ "BoutonFiltre()", &slot_7, QMetaData::Public },
	{ "slider1_valueChanged(int)", &slot_8, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Mat", parentObject,
	slot_tbl, 9,
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
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: ChargerImage(); break;
    case 1: Filtre((QImage*)static_QUType_varptr.get(_o+1)); break;
    case 2: Reconnaissance((QImage*)static_QUType_varptr.get(_o+1)); break;
    case 3: Reconnaitre(); break;
    case 4: AfficherLignes((p_liste)(*((p_liste*)static_QUType_ptr.get(_o+1))),(QImage*)static_QUType_varptr.get(_o+2)); break;
    case 5: BoutonLigne(); break;
    case 6: Filtre2((QImage*)static_QUType_varptr.get(_o+1)); break;
    case 7: BoutonFiltre(); break;
    case 8: slider1_valueChanged((int)static_QUType_int.get(_o+1)); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
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
