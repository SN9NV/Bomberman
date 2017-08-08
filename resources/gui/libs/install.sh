#!/usr/bin/env bash

install_name_tool -change @executable_path/../Frameworks/libCEGUIBase-0.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUIBase-0.dylib Bomberman
install_name_tool -change @executable_path/../Frameworks/libCEGUIOpenGLRenderer-0.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUIOpenGLRenderer-0.dylib Bomberman
install_name_tool -change @executable_path/../Frameworks/libCEGUIExpatParser.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUIExpatParser.dylib Bomberman
install_name_tool -change @executable_path/../Frameworks/libCEGUISILLYImageCodec.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUISILLYImageCodec.dylib Bomberman
install_name_tool -change @executable_path/../Frameworks/libCEGUICoreWindowRendererSet.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUICoreWindowRendererSet.dylib Bomberman
cd ../resources/gui/libs
install_name_tool -change @executable_path/../Frameworks/libfreetype_d.2.7.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libfreetype_d.2.7.dylib libCEGUIBase-0.dylib
install_name_tool -change @executable_path/../Frameworks/libCEGUIBase-0.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUIBase-0.dylib libCEGUIOpenGLRenderer-0.dylib
install_name_tool -change @executable_path/../Frameworks/libfreetype_d.2.7.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libfreetype_d.2.7.dylib libCEGUIOpenGLRenderer-0.dylib
install_name_tool -change @executable_path/../Frameworks/libCEGUIBase-0.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUIBase-0.dylib libCEGUIExpatParser.dylib
install_name_tool -change @executable_path/../Frameworks/libSILLY_d.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libSILLY_d.dylib libCEGUISILLYImageCodec.dylib
install_name_tool -change @executable_path/../Frameworks/libCEGUIBase-0.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUIBase-0.dylib libCEGUISILLYImageCodec.dylib
install_name_tool -change @executable_path/../Frameworks/libfreetype_d.2.7.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libfreetype_d.2.7.dylib libCEGUISILLYImageCodec.dylib
install_name_tool -change @executable_path/../Frameworks/libpng_d.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libpng_d.dylib libSILLY_d.dylib
install_name_tool -change @executable_path/../Frameworks/libjpeg_d.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libjpeg_d.dylib libSILLY_d.dylib
install_name_tool -change @executable_path/../Frameworks/libzlib_d.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libzlib_d.dylib libSILLY_d.dylib
install_name_tool -change @executable_path/../Frameworks/libzlib_d.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libzlib_d.dylib libpng_d.dylib
install_name_tool -change @executable_path/../Frameworks/libzlib_d.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libzlib_d.dylib libjpeg_d.dylib
install_name_tool -change @executable_path/../Frameworks/libCEGUIBase-0.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libCEGUIBase-0.dylib libCEGUICoreWindowRendererSet.dylib
install_name_tool -change @executable_path/../Frameworks/libfreetype_d.2.7.dylib $HOME/Desktop/SemesterThree/Bomberman/resources/gui/libs/libfreetype_d.2.7.dylib libCEGUICoreWindowRendererSet.dylib
