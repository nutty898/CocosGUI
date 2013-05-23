CocosGUI
=============

CocosGUI is a GUI framework based on Cocos2d-x. It's main components are CocoWidget and UIElement.

A cocos2d CCNode is wrapped into CRenderNode, while UIElement uses CRenderNode for drawing. As the result, 
UIElements, such as UISprite, UIPrimitive, is the foundation of this UI framework.

For CocoWidget, you can combine multiple UIElements to compose a complex widget.
Finally CocoWidgetContainer does the layout for CocoWidgets.

CocosGUI
