!isEmpty(QINGDB_PRI_INCLUDED):error("QinGDB.pri already included")
QINGDB_PRI_INCLUDED = 1

isEmpty(PRECOMPILED_HEADER):PRECOMPILED_HEADER = $$PWD/include/qingdb_pch.h

QINGDB_SOURCE_TREE = $$PWD

isEmpty(IDE_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    IDE_BUILD_TREE = $$clean_path($$OUT_PWD)
    IDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}


INCLUDEPATH += \
    $$QINGDB_SOURCE_TREE/ \
	$$QINGDB_SOURCE_TREE/include \
    $$QINGDB_SOURCE_TREE/libs \
    $$QINGDB_SOURCE_TREE/libs/QScintilla \
	
IDE_APP_PATH = $$IDE_BUILD_TREE/bin

isEmpty(IDE_LIBRARY_BASENAME) {
    IDE_LIBRARY_BASENAME = lib
}


contains(TEMPLATE, vc.*):vcproj = 1
IDE_APP_TARGET   = QinGDB
IDE_LIBRARY_PATH = $$IDE_BUILD_TREE/$$IDE_LIBRARY_BASENAME/QinGDB
IDE_BIN_PATH     = $$IDE_APP_PATH

LIBS += -L$$IDE_LIBRARY_PATH

win32 {
    DLLDESTDIR = $$IDE_APP_PATH
}

DESTDIR = $$IDE_LIBRARY_PATH
