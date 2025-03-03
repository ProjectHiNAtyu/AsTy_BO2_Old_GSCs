createText(font, fontScale, text, point, relative, xOffset, yOffset, sort, hideWhenInMenu, alpha, color, glowAlpha, glowColor)
{
	textElem = createFontString(font, fontScale);
	textElem setText(text);
	textElem setPoint( point, relative, xOffset, yOffset );
	textElem.sort = sort;
	textElem.hideWhenInMenu = hideWhenInMenu;
	textElem.alpha = alpha;
	textElem.color = color;
	textElem.glowAlpha = glowAlpha;
	textElem.glowColor = glowColor;
	self.result += 1;
	self notify("textset");
	textElem setText(text);
	return textElem;
}
createRectangle(align, relative, x, y, shader, width, height, color, alpha, sort)
{
        barElemBG = newClientHudElem( self );
        barElemBG.elemType = "bar";
        if ( !level.splitScreen )
        {
                barElemBG.x = -2;
                barElemBG.y = -2;
        }
        barElemBG.width = width;
        barElemBG.height = height;
        barElemBG.align = align;
        barElemBG.relative = relative;
        barElemBG.xOffset = 0;
        barElemBG.yOffset = 0;
        barElemBG.children = [];
        barElemBG.sort = sort;
        barElemBG.color = color;
        barElemBG.alpha = alpha;
        barElemBG setParent( level.uiParent );
        barElemBG setShader( shader, width , height );
        barElemBG.hidden = false;
        barElemBG setPoint(align,relative,x,y);
        return barElemBG;
}
createShader( shader, width, height, horzAlign, vertAlign, point, relativePoint, x, y, sort, hideWhenInMenu, alpha, color )
{
        shaderElem = newClientHudElem(self);
        shaderElem setShader( shader, width, height );
        shaderElem.horzAlign = horzAlign;
        shaderElem.vertAlign = vertAlign;
        shaderElem.alignY = point;
        shaderElem.alignX = relativePoint;
        shaderElem.x = x;
        shaderElem.y = y;
        shaderElem.sort = sort;
        shaderElem.hideWhenInMenu = hideWhenInMenu;
        if(isDefined(alpha)) shaderElem.alpha = alpha;
        else shaderElem.alpha = 1;
        shaderElem.color = color;
        return shaderElem;
}
 
destroyOnDeathOrUpdate(client)
{
        client endon("disconnect");
        client waittill_any("death","Update","Menu_Is_Closed");
        self destroy();
}
 
destroyOnAny( elem, a, b, c, d )
{
    if(!isDefined(a))
        a = "";
    if(!isDefined(b))
        b = "";
    if(!isDefined(c))
        c = "";
        if(!isDefined(d))
                d = "";
    self waittill_any("death",a,b,c,d);
    elem destroy();
}

WelcomeMessage()
{
	self thread init_WelcomeMessage("Project ^F^1F^0a^1t^0e^3/^1E^0x^1c^0a^1^0l^1i^0b^1u^0r", 1, "Welcome, ^5" + self.name + "^7!!", (1, 1, 0), 9, 0);
	self iPrintln("^6[{+speed_throw}] + [{+actionslot 1}] : ^2Open Menu");
	self iPrintln("^6[{+speed_throw}] + [{+melee}] : ^2Open Menu");
}

Test()
{
        self iPrintLnBold(self.Menu["Scroller"][self.Menu["Current"]]);
}

elemMoveX(time, input)
{
	self moveOverTime(time);
	self.x = input;
}
elemMoveY(time, input)
{
	self moveOverTime(time);
	self.y = input;
}
elemMove(time, inputX, inputY)
{
	self moveOverTime(time);
	self.x = inputX;
	self.y = inputY;
}
elemFade(time, alpha)
{
	self fadeOverTime(time);
	self.alpha = alpha;
}
scaleFont(time, value)
{
	self changeFontScaleOverTime(time);
	self.fontScale = value;
}
elemColor(Time, Color)
{
	self fadeOverTime(Time);
	self.color = Color;
}
elemGlow(time, g_color, g_alpha)
{
	self fadeOverTime(time);
	self.glowColor = g_color;
	self.Glowalpha = g_alpha;
}
fontIn(Time, Alpha, TimeII, Size)
{
	self fadeOverTime(Time);
	self.alpha = Alpha;
	self changeFontScaleOverTime(TimeII);
	self.fontScale = Size;
}

OverflowFix()
{  
	self endon("disconnect");
	self.result = 0;
	self.FlowFixMenuOpen = 0;
	flowfix = self createFontString("default", 1.5); //createFontString level.test = createServerFontString("default", 1.5);
	flowfix setText("Jwm614");
	flowfix.alpha = 0;
	flowfix setPoint("CENTER", "CENTER", 1000, 1000);
	for(;;)
	{
		self waittill("textset");
		if(self.result >= 225)
		{
			flowfix ClearAllTextAfterHudElem();
			self.result = 0;
			wait 0.01;
			foreach(player in level.players)
			{
				if(player.MenuOpen == true)
					player ReCreateMenuOpen();
			}
		}
	}
}

ReCreateMenuOpen()
{
	if(self.MenuOpen == true)
	{
		if(isDefined(self.Menu["Parents"][self.Menu["Current"]]))
			self enterMenu(self.Menu["Current"]);
		else
			self enterMenu("Main");
	}
}

MethodDesigns()
{
	self.BlackScreen = self createRectangle("CENTER", "CENTER", 0, 0, "white", 5000, 5000, (0, 0, 0), 0, 1);
	self.WhiteScreen = self createRectangle("CENTER", "CENTER", 0, 0, "white", 5000, 5000, (1, 1, 1), 0, 1);
}















