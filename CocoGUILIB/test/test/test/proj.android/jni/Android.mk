LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../../../../CocoGUILIB/BaseClasses/Graphics/UIElement.cpp \
                   ../../../../../CocoGUILIB/BaseClasses/Widget/CocoContainerWidget.cpp \
                   ../../../../../CocoGUILIB/BaseClasses/Widget/CocoRootWidget.cpp \
		   ../../../../../CocoGUILIB/BaseClasses/Widget/CocoWidget.cpp \
                   ../../../../../CocoGUILIB/CGraphics/CClipAbleLayerColor.cpp \
                   ../../../../../CocoGUILIB/CGraphics/CClipAbleSprite.cpp \
                   ../../../../../CocoGUILIB/CGraphics/CLabelAtlas.cpp \
                   ../../../../../CocoGUILIB/CGraphics/CPrimitivesNode.cpp \
                   ../../../../../CocoGUILIB/CGraphics/CRenderNode.cpp \
                   ../../../../../CocoGUILIB/CGraphics/CTextField.cpp \
                   ../../../../../CocoGUILIB/CGraphics/GUINodeRGBA.cpp \
                   ../../../../../CocoGUILIB/Component/CocoButton.cpp \
                   ../../../../../CocoGUILIB/Component/CocoCheckBox.cpp \
                   ../../../../../CocoGUILIB/Component/CocoImageView.cpp \
                   ../../../../../CocoGUILIB/Component/CocoLabel.cpp \
                   ../../../../../CocoGUILIB/Component/CocoLabelAtlas.cpp \
                   ../../../../../CocoGUILIB/Component/CocoLoadingBar.cpp \
                   ../../../../../CocoGUILIB/Component/CocoPanel.cpp \
                   ../../../../../CocoGUILIB/Component/CocoScrollView.cpp \
                   ../../../../../CocoGUILIB/Component/CocoSlider.cpp \
                   ../../../../../CocoGUILIB/Component/CocoTextArea.cpp \
                   ../../../../../CocoGUILIB/Component/CocoTextButton.cpp \
                   ../../../../../CocoGUILIB/Component/CocoTextField.cpp \
                   ../../../../../CocoGUILIB/System/CCSReader.cpp \
                   ../../../../../CocoGUILIB/System/CocoStudioGUI.cpp \
                   ../../../../../CocoGUILIB/System/DictionaryHelper.cpp \
                   ../../../../../CocoGUILIB/System/InputLayer.cpp \
		   ../../../../../CocoGUILIB/System/UIInputManager.cpp \
		   ../../../../../CocoGUILIB/System/UIScene.cpp \
		   ../../../../../CocoGUILIB/System/UISystem.cpp \
                   ../../../../../CocoGUILIB/System/Json/CSContentJsonDictionary.cpp \
                   ../../../../../CocoGUILIB/System/Json/lib_json/json_value.cpp \
                   ../../../../../CocoGUILIB/System/Json/lib_json/json_reader.cpp \
                   ../../../../../CocoGUILIB/System/Json/lib_json/json_writer.cpp \
		   ../../../../../CocoGUILIB/UIElements/UILabelAtlas.cpp \
		   ../../../../../CocoGUILIB/UIElements/UIScale9Sprite.cpp \
		   ../../../../../CocoGUILIB/UIElements/UISprite.cpp \
                   ../../../../../CocoGUILIB/UIElements/UIText.cpp \
                   ../../../../../CocoGUILIB/UIElements/UITextArea.cpp \
                   ../../../../../CocoGUILIB/UIElements/UITextField.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/BaseClasses/Graphics \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/BaseClasses/Widget \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/CGraphics \
		     $(LOCAL_PATH)/../../../../../CocoGUILIB/Component \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/System \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/System/Json/json \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/System/Json \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/System/Json/lib_json \
                    $(LOCAL_PATH)/../../../../../CocoGUILIB/UIElements \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_extension_static

LOCAL_CFLAGS := -fexceptions

include $(BUILD_SHARED_LIBRARY)

$(call import-module, extensions)

