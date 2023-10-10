QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    neural_network_core/cell.cpp \
    neural_network_core/data.cpp \
    neural_network_core/neural_network.cpp \
    gui/form_hidden_layers_new.cpp \
    gui/form_hidden_layers_open.cpp \
    gui/form_input_layer_new.cpp \
    gui/form_input_layer_open.cpp \
    gui/form_main.cpp \
    gui/form_nn_file.cpp \
    gui/form_other_settings_new.cpp \
    gui/form_other_settings_open.cpp \
    gui/form_output_layer_new.cpp \
    gui/form_output_layer_open.cpp \
    gui/form_run.cpp \
    gui/form_samples_file.cpp \
    gui/graph_ew.cpp \
    gui/threads.cpp \
    main.cpp

HEADERS += \
    neural_network_core/cell.h \
    neural_network_core/data.h \
    neural_network_core/defines_core.h \
    neural_network_core/neural_network.h \
    gui/defines_gui.h \
    gui/form_hidden_layers_new.h \
    gui/form_hidden_layers_open.h \
    gui/form_input_layer_new.h \
    gui/form_input_layer_open.h \
    gui/form_main.h \
    gui/form_nn_file.h \
    gui/form_other_settings_new.h \
    gui/form_other_settings_open.h \
    gui/form_output_layer_new.h \
    gui/form_output_layer_open.h \
    gui/form_run.h \
    gui/form_samples_file.h \
    gui/graph_ew.h \
    gui/threads.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
