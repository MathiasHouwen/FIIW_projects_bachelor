#ifndef CHATURAJI_GLOBAL_H
#define CHATURAJI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CHATURAJI_LIBRARY)
#define CHATURAJI_EXPORT Q_DECL_EXPORT
#else
#define CHATURAJI_EXPORT Q_DECL_IMPORT
#endif

#endif // CHATURAJI_GLOBAL_H
