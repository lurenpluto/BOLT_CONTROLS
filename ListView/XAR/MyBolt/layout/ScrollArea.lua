function OnInitControl(self)
	self:SetLimitChild(true)
	self:GetAttribute().ViewToSourceMap={}
	-- self:GetAttribute().ItemContainers[i]为界面上可以看见的第i个button
	self:GetAttribute().ItemContainers={}
	
	-- Scroll Area Rectangle
	self:GetAttribute().ScrollSizeAttributes = {
		["ScrollAreaWidth"] = 0,
		["ScrollAreaHeight"] = 0
	}
	
	self:GetAttribute().ScrollAttributes = {
		["Capacity"] = 0,
		["MaximumScrollPosV"] = 0,
		["ScrollPosV"] = 0, 
		["MaximumScrollPosH"] = 0,
		["ScrollPosH"] = 0, 
		["FirstVisibleIndex"] = 1,
		["LastVisibleIndex"] = 1
	}
	
	-- 鼠标是否按下，鼠标上一次移动到什么位置，什么时间
	self:GetAttribute().MouseInfo={}
	-- 预留,有想要在其他文件里调用的私有方法
	self:GetAttribute().PrivateMethods = {}
	self:GetAttribute().PrivateMethods.getVisibleItemObject = getVisibleItemObject
	
	self:GetAttribute().HeaderWidths = {}
	self:GetAttribute().RowHeight = nil
end

function GetFirstVisibleIndex(self)
	return self:GetAttribute().ScrollAttributes["FirstVisibleIndex"]
end

function getVisibleItemObject(self, row, column)
	if #(self:GetAttribute().ViewToSourceMap) == 0 then 
		return nil 
	end
	if self:GetAttribute().ViewToSourceMap[math.ceil(self:GetAttribute().ScrollAttributes["Capacity"]+1)] == nil then
		return nil 
	end
	if row < self:GetAttribute().ViewToSourceMap[0] or row > self:GetAttribute().ViewToSourceMap[self:GetAttribute().ScrollAttributes["Capacity"]+1] then return nil end
	local container = self:GetAttribute().ItemContainers[row-self:GetAttribute().ViewToSourceMap[0]]
	return container:GetAttribute().Children[column]
end

function SetItemFactory(self, userdata, name, callbackTable)
-- 会影响到：行高，列宽，所以会影响scroll area size，所以需要重新计算尺寸+refresh

	self:SetScrollPosV(0)
	local attr = self:GetAttribute()
	attr.itemFactoryCallbackTable = callbackTable
	attr.itemFactoryUserData = userdata
	
	local expected = {"CreateObject", -- Optional if template/control name provided
		"GetRowHeight", -- Optional
		"GetColumnWidth", -- Optional
		"SetItemPos2", -- Optional
		"SetItemData"}
		
	if attr.itemFactoryCallbackTable.GetRowHeight == nil then
		attr.itemFactoryCallbackTable.GetRowHeight = 
			function(userdata)
				return 50
			end
	end
	
	if attr.itemFactoryCallbackTable.GetColumnWidth == nil then
		attr.itemFactoryCallbackTable.GetColumnWidth = 
			function(userdata, column, widthInAll)
				local columnCount = self:GetColumnCount()
				return widthInAll / columnCount
			end
	end
	
	if attr.itemFactoryCallbackTable.CreateObject == nil then
		attr.itemFactoryCallbackTable.CreateObject = 
			function(userdata, column,row)
				local templateManager = XLGetObject("Xunlei.UIEngine.TemplateManager")
				local template = templateManager:GetTemplate(name, "ObjectTemplate")
				itemObj = template:CreateInstance("ob2j"..column)
				if itemObj then
					return itemObj 
				else
					local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
					local itemObj = objFactory:CreateUIObject(nil,name)
				end
				return itemObj
			end
	end
	
	if attr.itemFactoryCallbackTable.SetItemPos2 == nil then
		attr.itemFactoryCallbackTable.SetItemPos2 = 
			function(userdata, itemObj, l,t,w,h)
				itemObj:SetObjPos2(l,t,w,h)
			end
	end
	
	local containAllRequiredMethod = CheckMethodWithAlert(expected, attr.itemFactoryCallbackTable, "ItemFactory")
	
	local innerLayout = self:GetControlObject("scrollarea.layout")
	innerLayout:RemoveAllChild()
	self:GetAttribute().ItemContainers = {}
end

-- 创建足够多的container和itemobj, 更新它们的内容
function UpdateItems(self)
	syncSizeAndItemCount(self)
	refreshItems(self)
end

function refreshItems(self)
-- 最多的调用是滚动的时候，不要把scroll area 大小改变导致的事情放在这里
	local innerLayout = self:GetControlObject("scrollarea.layout")
	local colCount = self:GetColumnCount()
	local funSetItemData = self:GetAttribute().itemFactoryCallbackTable.SetItemData
	for i = 0,self:GetAttribute().ScrollAttributes["Capacity"]+1 do
		local container = self:GetAttribute().ItemContainers[i]
		local row=self:GetAttribute().ViewToSourceMap[i]
		if row <= self:GetRowCount() then
			container:SetVisible(true)
			container:SetChildrenVisible (true)
			for col = 1, colCount do
				local itemData = self:GetItemAtIndex(row, col, i)
				local children = container:GetAttribute().Children
				local itemObj = children[col]
				funSetItemData(self:GetAttribute().itemFactoryUserData, itemObj, itemData, row, col)
			end
		else
			container:SetVisible(false)
			container:SetChildrenVisible (false)
		end
	end
end

function syncSizeAndItemCount(self)
	-- 在内容或尺寸改变时调用，不要在refresh时调用
	resizeInnerLayout(self)
	resizeCapacity(self)
	resizeScrollRange(self)
	syncViewToSourceTable(self)
	createEnoughItems(self)
end

function resizeInnerLayout(self)
	local l,t,r,b = self:GetObjPos()
	local rowHeight = getRowHeight(self)
	local columnCount = self:GetColumnCount()
	local funGetColWidth = self:GetAttribute().itemFactoryCallbackTable.GetColumnWidth
	local width = 0
	for col=1,columnCount do
		self:GetAttribute().HeaderWidths[col]=funGetColWidth(self:GetAttribute().itemFactoryUserData, col, r-l)
		width = width+self:GetAttribute().HeaderWidths[col]
	end
	local innerLayout = self:GetControlObject("scrollarea.layout")
	local il, it, ir, ib = innerLayout:GetObjPos()
	innerLayout:SetObjPos(0,it,width,it+b-t+rowHeight+rowHeight)
end

function resizeCapacity(self)
	local l,t,r,b = self:GetObjPos()
	local expectedCapacity = math.ceil((b - t)/getRowHeight(self))
	if expectedCapacity ~= self:GetAttribute().ScrollAttributes["Capacity"] then
		self:GetAttribute().ScrollAttributes["Capacity"] = expectedCapacity
		local expectedPreloadDataCount = 2*(math.ceil(expectedCapacity))
		if self:GetAttribute().PreloadDataCount > 0 and self:GetAttribute().PreloadDataCount < expectedPreloadDataCount then
			self:GetAttribute().PreloadDataCount = expectedPreloadDataCount
		end
	end
end

function resizeScrollRange(self)
	local l,t,r,b = self:GetObjPos()
	local scrollWidth, scrollHeight = self:GetScrollAreaSize()
	setMaximumV(self, scrollHeight>b-t and scrollHeight-(b-t) or 0)
	setMaximumH(self, scrollWidth>r-l and scrollWidth-(r-l) or 0)
end

-- This should be called when size changed
function syncViewToSourceTable(self)
	local scrollPos = self:GetAttribute().ScrollAttributes["ScrollPosV"]
	local innerLayout = self:GetControlObject("scrollarea.layout")
	local il, it, ir, ib = innerLayout:GetObjPos()
	local innerLayoutTopIsAtScrollPos = scrollPos+it
	local rowHeight = getRowHeight(self)
	local zeroItem = math.ceil((innerLayoutTopIsAtScrollPos+rowHeight)/rowHeight)
	for i=0,math.ceil(self:GetAttribute().ScrollAttributes["Capacity"]+1) do
		self:GetAttribute().ViewToSourceMap[i]=i+zeroItem
	end
end

function createEnoughItems(self)
	if self:GetAttribute().ScrollAttributes["Capacity"]+1 >= table.maxn(self:GetAttribute().ItemContainers)+1 then
		local innerLayout = self:GetControlObject("scrollarea.layout")
		local attr = self:GetAttribute()
		local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
		local userData = attr.itemFactoryUserData
		local itemFactoryCallbackTable = attr.itemFactoryCallbackTable
		local funCreateItem = itemFactoryCallbackTable.CreateObject
		local funGetColWidth = itemFactoryCallbackTable.GetColumnWidth
		local funSetItemPos2 = itemFactoryCallbackTable.SetItemPos2
		local colCount = self:GetColumnCount()
		local colWidthTable = {}
		local left,top,right,bottom = self:GetObjPos()
		for col = 1, colCount do
			colWidthTable[col] = 
			funGetColWidth(userData, col, right-left)
		end
		top = 0
		for i = 0,self:GetAttribute().ScrollAttributes["Capacity"]+1 do
			if self:GetAttribute().ItemContainers[i] == nil then
				local container = objFactory:CreateUIObject("container"..i,"ListView.ItemContainer")
				container:SetLimitChild(true)
				top = getRowHeight(self)*i
				container:SetObjPos2(0, top, right-left, getRowHeight(self))
				self:GetAttribute().ItemContainers[i]=container
				innerLayout:AddChild(container)
				-- Create item object and place it into container
				local containerLayout = container:GetControlObject("container.layout")
				local iL, iT, iW, iH;
				iL = 0;
				iT = 0;
				iH = getRowHeight(self)
				local children = {}
				for col = 1, colCount do
					local itemObj = funCreateItem(userData, col, i)
					iW = colWidthTable[col]
					funSetItemPos2(userData, itemObj, iL, iT, iW, iH)
					iL = iL + iW
					containerLayout:AddChild(itemObj)
					children[col] = itemObj
				end
				container:GetAttribute().Children = children
			end
		end
	end
end

function setMaximumV(self,newMax)
	if newMax ~= self:GetAttribute().ScrollAttributes["MaximumScrollPosV"] and newMax >= 0 then
		self:GetAttribute().ScrollAttributes["MaximumScrollPosV"] = newMax
	end
end

function setMaximumH(self, newMax)
	if newMax ~= self:GetAttribute().ScrollAttributes.MaximumScrollPosH and newMax>=0 then
		self:GetAttribute().ScrollAttributes.MaximumScrollPosH = newMax
	end
end

function UpdateScrollAreaSize(self)
	-- 重新计算在给定ItemDelegate和DataModel时需要的scrollArea有多大. 只做计算,不做处理,处理有另一个后面调用的方法来做
	local l,t,r,b = self:GetObjPos()
	local attr = self:GetAttribute()
	local rowHeight = getRowHeight(self)
	local rowCount = self:GetRowCount()
	attr.ScrollSizeAttributes.ScrollAreaHeight = rowHeight * rowCount
	
	local columnCount = self:GetColumnCount()
	local funGetColWidth = attr.itemFactoryCallbackTable.GetColumnWidth
	local widthRequired = 0
	
	for col = 1, columnCount do
		local colWidth = funGetColWidth(attr.itemFactoryUserData, col, r-l)
		widthRequired = widthRequired+colWidth
	end
	attr.ScrollSizeAttributes.ScrollAreaWidth = widthRequired
end
	
function GetScrollAreaSize(self)
	return self:GetAttribute().ScrollSizeAttributes.ScrollAreaWidth, self:GetAttribute().ScrollSizeAttributes.ScrollAreaHeight
end

function GetScrollPosH(self)
	return self:GetAttribute().ScrollAttributes.ScrollPosH
end

function SetScrollPosH(self, pos)
	local oldPos = self:GetAttribute().ScrollAttributes.ScrollPosH
	self:GetAttribute().ScrollAttributes.ScrollPosH = pos
	local innerLayout = self:GetControlObject("scrollarea.layout")
	local l,t,r,b = self:GetObjPos()
	local il, it, ir, ib = innerLayout:GetObjPos()
	if pos>=0 and pos<=self:GetAttribute().ScrollAttributes.MaximumScrollPosH and pos~=oldPos then
		innerLayout:SetObjPos(0-pos,it,r-l-pos,ib)
		self:FireExtEvent("HorizontalScrollPosChanged", oldPos, pos)
	end
end

function OnLButtonDown(self,x,y)
	self:GetAttribute().MouseInfo["MouseDown"] = true
	self:GetAttribute().MouseInfo["Y"] = y
	self:GetAttribute().MouseInfo["Time"]=os.clock()*1000
	self:GetAttribute().MouseInfo["Y2"] = y
	self:GetAttribute().MouseInfo["Time2"]=os.clock()*1000
end

function OnLButtonUp(self, x, y)
	if self:GetAttribute().MouseInfo["MouseDown"] == true then
		mouseUp(self, x,y)
	end
end

function OnMouseMove(self, x, y)
	if self:GetAttribute().MouseInfo["MouseDown"] == true then
		local attr = self:GetAttribute()
		local curPos = self:GetAttribute().ScrollAttributes["ScrollPosV"]
		local toPos = curPos - y + self:GetAttribute().MouseInfo["Y"]
		self:SetScrollPosV(toPos)
		--记下最近两次（时间，位置），为最终鼠标放开时计算最后一次移动速度积累数据
		self:GetAttribute().MouseInfo["Y2"]=self:GetAttribute().MouseInfo["Y"]
		self:GetAttribute().MouseInfo["Time2"]=self:GetAttribute().MouseInfo["Time"]
		self:GetAttribute().MouseInfo["Y"] = y
		self:GetAttribute().MouseInfo["Time"]=os.clock()*1000
	end
end

function OnMouseLeave(self, x, y)
	local left, top, right, bottom = self:GetObjPos()
	if x <= 0 or x >= right-left or y <= 0 or y >= bottom-top then
		if self:GetAttribute().MouseInfo["MouseDown"]==true then
			mouseUp(self, x,y)
		end
	end
end

function mouseUp(self, x, y)
--Extract same code when mouse button up or mouse button leave scroll area
	self:GetAttribute().MouseInfo["MouseDown"] = false
	local distance = self:GetAttribute().MouseInfo["Y"]-self:GetAttribute().MouseInfo["Y2"]
	local duration = self:GetAttribute().MouseInfo["Time"]-self:GetAttribute().MouseInfo["Time2"]
	if duration <= 0 then duration = 1 end
	local lastMove = os.clock()*1000-self:GetAttribute().MouseInfo["Time"]
	--鼠标放开时，如果认为这是一个延时滑动事件，就再滚一会儿
	--滚动效果取决于鼠标离开时的移动速度
	if math.abs(distance)/duration >= 1 and lastMove < 10 then
		local speed = -distance/duration * 50
		local attr = self:GetAttribute()
		local from = self:GetAttribute().ScrollAttributes["ScrollPosV"]
		scrollActionFrom(self, from, speed)
	end
end 

function OnMouseWheel(self,x,y,distance)
-- 鼠标中键滚动时，简单地上下移动containers
	local curPos = self:GetAttribute().ScrollAttributes["ScrollPosV"]
	local toPos = curPos-distance/10
	self:SetScrollPosV(toPos)
end

function SetScrollPosV(self,newValue)
	if newValue ~= self:GetAttribute().ScrollAttributes["ScrollPosV"] then
		if newValue <= self:GetAttribute().ScrollAttributes["MaximumScrollPosV"] and newValue >= 0 then
			local oldValue = self:GetAttribute().ScrollAttributes["ScrollPosV"]
			local distanceV = newValue-self:GetAttribute().ScrollAttributes["ScrollPosV"]
			self:GetAttribute().ScrollAttributes["ScrollPosV"]= newValue
			move(self, -distanceV)
			self:FireExtEvent("OnScrollPosChange")
			-- 触发ScrollArea自定义事件, 带参数的方法
			-- 监听事件的方法见 ListView.lua, 搜索VerticalScrollPosChanged
			-- 也看, HorizontalScrollPosChanged
			self:FireExtEvent("VerticalScrollPosChanged", oldValue, newValue)
			local rh = getRowHeight(self)
			local first = math.floor(newValue/rh)+1
			local last = math.floor((newValue+getPageHeight(self))/rh)+1
			if first ~= self:GetAttribute().ScrollAttributes["FirstVisibleIndex"] or last ~= self:GetAttribute().ScrollAttributes["LastVisibleIndex"] then
				self:GetAttribute().ScrollAttributes["FirstVisibleIndex"] = first
				self:GetAttribute().ScrollAttributes["LastVisibleIndex"] = last
				self:FireExtEvent("VisibleItemChanged", first, last)
			end
		end
	end
end

function move(self, distanceV)
	local owner = self:GetOwner()
	local needRefresh = false;
	local innerLayout = self:GetControlObject("scrollarea.layout")
	if innerLayout then
		local left,top,right,bottom=innerLayout:GetObjPos()
		innerLayout:SetObjPos(left, top + distanceV, right, bottom+distanceV)
		
		left, top, right, bottom = innerLayout:GetObjPos()
		while top + getRowHeight(self) < 0 do
			innerLayout:SetObjPos(left, top+getRowHeight(self), right, bottom+getRowHeight(self))
			for i=0,self:GetAttribute().ScrollAttributes["Capacity"]+1 do
				self:GetAttribute().ViewToSourceMap[i]=self:GetAttribute().ViewToSourceMap[i]+1
			end
			top = top + getRowHeight(self)
			needRefresh = true
		end
		while top > 0 do 
			innerLayout:SetObjPos(left,top-getRowHeight(self),right,bottom-getRowHeight(self))
			for i=0,self:GetAttribute().ScrollAttributes["Capacity"]+1 do
				self:GetAttribute().ViewToSourceMap[i]=self:GetAttribute().ViewToSourceMap[i]-1
			end
			top = top - getRowHeight(self)
			needRefresh = true
		end
	end
	if needRefresh then
		refreshItems(self)
	end
end

function GetScrollPosV(self)
	return self:GetAttribute().ScrollAttributes["ScrollPosV"]
end

function PageUp(self)
	local attr = self:GetAttribute()
	local pageHeight = getPageHeight(self)
	local newValue = self:GetAttribute().ScrollAttributes["ScrollPosV"] - pageHeight
	if newValue < 0 then
		newValue=0
	end
	if newValue < self:GetAttribute().ScrollAttributes["ScrollPosV"] then
		scrollActionFromTo(self,self:GetAttribute().ScrollAttributes["ScrollPosV"], newValue)
	end
end

function scrollActionFrom(self, from, speed)
--仅指定初始速度，用递归匀速动画Scroll.ani实现减速停靠
	local owner = self:GetOwner()
	if math.abs(speed) <= 1 then
		self:SetScrollPosV(from+speed)
		return
	end
	local aniFactory = XLGetObject("Xunlei.UIEngine.AnimationFactory")
	myAni = aniFactory:CreateAnimation("Scroll.ani")
	myAni:SetTotalTime(20)
	local aniAttr = myAni:GetAttribute()
	aniAttr.from = from
	aniAttr.speed = speed
	aniAttr.obj = self
	
	local function onAniFinish(self,oldState,newState)
		if newState == 4 then
			local aniAttr = self:GetAttribute()
			scrollActionFrom(aniAttr.obj, aniAttr.from+aniAttr.speed, aniAttr.speed*0.8)
		end
	end
	
	myAni:AttachListener(true,onAniFinish)
	owner:AddAnimation(myAni)
	myAni:Resume()
end

function scrollActionFromTo(self,from,to)
--指定从起点到终点，计算滑行时间，由DynamicScroll.ani计算每个时间点位置
	local owner = self:GetOwner()
	
	local aniFactory = XLGetObject("Xunlei.UIEngine.AnimationFactory")
	myAni = aniFactory:CreateAnimation("DynamicScroll.ani")
	local totalTime = 0
	if from < to then
		totalTime = (to - from) * 3
	else
		totalTime = (from - to) * 3
	end

	myAni:SetTotalTime(totalTime) 
	local aniAttr = myAni:GetAttribute()
	aniAttr.from = from
	aniAttr.to = to
	aniAttr.obj = self
	
	local function onAniFinish(self,oldState,newState)
		if newState == 4 then
		--To ensure arriving
			aniAttr.obj:SetScrollPosV(to)
		end
	end
	
	myAni:AttachListener(true,onAniFinish)
	owner:AddAnimation(myAni)
	myAni:Resume()
end

function PageDown(self)
	local attr = self:GetAttribute()
	local pageHeight = getPageHeight(self)
	local newValue = self:GetAttribute().ScrollAttributes["ScrollPosV"] + pageHeight
	if newValue > self:GetAttribute().ScrollAttributes["MaximumScrollPosV"] then
		newValue=self:GetAttribute().ScrollAttributes["MaximumScrollPosV"]
	end
	if newValue > self:GetAttribute().ScrollAttributes["ScrollPosV"] then
		scrollActionFromTo(self,self:GetAttribute().ScrollAttributes["ScrollPosV"], newValue)
	end
end

function getPageHeight(self)
	local l,t,r,b = self:GetObjPos()
	return b-t
end

function getRowHeight(self)
	if self:GetAttribute().RowHeight ==  nil then
		local attr = self:GetAttribute()
		local callbackTable = attr.itemFactoryCallbackTable
		if callbackTable ~= nil then
			local funGetRowHeight = callbackTable.GetRowHeight
				self:GetAttribute().RowHeight = funGetRowHeight(attr.itemFactoryUserData)
		end
	end
	return self:GetAttribute().RowHeight
end

function GetColumnWidthList(self)
	return self:GetAttribute().HeaderWidths
end

function OnPosChange(self, oldLeft, oldTop, oldRight, oldBottom, newLeft, newTop, newRight, newBottom)
	if oldBottom-oldTop~=newBottom-newTop then
		local rqw, rqh = self:GetScrollAreaSize()
		local containers = self:GetAttribute().ItemContainers
		if #containers > 0 then
			-- self:SetScrollPosV(0)
			self:UpdateItems()
		end
	end
end