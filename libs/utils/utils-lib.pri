dll {
    DEFINES += QINGDB_UTILS_LIB
} else {
    DEFINES += QINGDB_UTILS_STATIC_LIB
}

CONFIG += exceptions 

SOURCES += \
    $$PWD/styledbar.cpp \

HEADERS += \
    $$PWD/styledbar.h \
