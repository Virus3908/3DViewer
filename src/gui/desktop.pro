QT       += core gui widgets opengl openglwidgets


CONFIG += c++17

QMAKE_CXXFLAGS += -Wall -Werror -Wextra

TARGET = 3DViewer

CONFIG += link_pkgconfig
PKGCONFIG += opencv4

ICON = icon/icon.ico

SOURCES += \
    s21_engine.cc \
    s21_frontend.cc \
    menu/s21_menu_widget.cc \
    OpenGL/s21_viewer_widget.cc \
    control/s21_control_widget.cc \
    control/s21_settings_widget.cc \
    infortmation/s21_information_widget.cc \
    ../controller/s21_controller.cc \
    ../backend/s21_backend.cc \
    ../backend/matrix/s21_matrix.cc \
    ../backend/model/s21_model.cc \
    ../backend/transform/s21_transform.cc

HEADERS += \
    s21_frontend.h \
    s21_gui_defines.h \
    menu/s21_menu_widget.h \
    OpenGL/s21_viewer_widget.h \
    control/s21_control_widget.h \
    control/s21_settings_widget.h \
    infortmation/s21_information_widget.h \
    ../controller/s21_controller.h \
    ../backend/s21_backend.h \
    ../backend/matrix/s21_matrix.h \
    ../backend/model/s21_model.h \
    ../backend/transform/s21_transform.h \
    ../common/s21_common.h

RESOURCES += resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
