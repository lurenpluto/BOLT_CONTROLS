local mdDataModel = XLLoadModule(lua_code_dir.."TestDataModel.lua")
local GetXmlDataModelObject = mdDataModel.GetXmlDataModelObject

local mdItemFactory = XLLoadModule(lua_code_dir.."ItemFactory.lua")
local GetItemFactory = mdItemFactory.GetItemFactory

local mdSimple = XLLoadModule(lua_code_dir.."SimpleItemFactoryAndDataModel.lua")
local GetTextItemFactory = mdSimple.GetTextItemFactory
local GetSimpleDataModelObject = mdSimple.GetSimpleDataModelObject

local GlobalListView = nil 
function OnInitControl_ListView(self)
	GlobalListView = self
	initListViewWithCppModel(self)
end

function OnDestroy_ListView(self)
end

function OnDestroy(self)
	local tree = self:GetBindUIObjectTree()
	local rootObj = tree:GetRootObject()
	rootObj:RemoveAllChild()
end

function initListViewWithSimpleModel(self)
	local itemFactoryUserData, itemFactoryCallbackTable = GetTextItemFactory()
	self:SetItemFactory(itemFactoryUserData, nil, itemFactoryCallbackTable)
	
	local dataModelUserData, dataModelCallbackTable = GetSimpleDataModelObject()
	self:SetDataModel(dataModelUserData, dataModelCallbackTable)
end

function initListViewWithCppModel(self)
	-- Setup item factory
	local itemFactoryUserData, itemFactoryCallbackTable = GetItemFactory()
	self:SetItemFactory(itemFactoryUserData, nil, itemFactoryCallbackTable)

	-- Setup data model,  by default lua table is applied. 
	-- -- 示例代码 Custom data model import by "require"
	local dataModelUserData, dataModelCallbackTable = GetXmlDataModelObject("XmlDataModel", "Music.xml")
	self:SetDataModel(dataModelUserData, dataModelCallbackTable)
	
	-- -- user can: 1. specify another lua table as data model;  
	-- -- 示例代码： Local table data model
	-- local dt = {{"cats"},{"eats"},{"fish"}}
	-- self:SetDataTable(dt)
	
	-- 示例代码 set header data
	self:SetHeaderNameList({"Cover", "Name", "Dir"})
	
	local function OnListViewHorizontalScrollPosChanged(listViewObject, listViewEventName, oldPos, newPos)
		-- 监听自定义控件自定义事件方法二:
		-- 这样做的好处是不想继续监听的时候可以根据 AttachListener 返回的 cookie 移除监听
	end
	local cookie, ret = self:AttachListener("HorizontalScrollPosChanged", true, OnListViewHorizontalScrollPosChanged)
	if ret then
		-- 移除对事件 HorizontalScrollPosChanged 的监听, 所以上面的 AttachListener 不再有效
		self:RemoveListener("HorizontalScrollPosChanged", cookie)
	end
end

function ChangeModel(self)
	if GlobalListView ~=  nil then
		if self:GetText()=="加载Lua Data Model" then
			initListViewWithSimpleModel(GlobalListView)
			self:SetText("加载C++ Data Model")
		elseif self:GetText()=="加载C++ Data Model" then
			initListViewWithCppModel(GlobalListView)
			self:SetText("加载Lua Data Model")
		end
	end
end

function scroll_down_OnLButtonDown(self)
	local parent = self:GetParent():GetParent()
	local count = parent:GetChildCount()
	for i=0,count-1 do
		local obj = parent:GetChildByIndex(i)
		if obj:GetID() == "listview" then
			local scroll = obj
			scroll:PageDown()
		end
	end
end

function scroll_up_OnLButtonDown(self)
	local parent = self:GetParent():GetParent()
	local count = parent:GetChildCount()
	
	for i=0,count-1 do
		local obj = parent:GetChildByIndex(i)
		if obj:GetID() == "listview" then
			local scroll = obj
			scroll:PageUp()
		end
	end
end

function close_btn_OnLButtonDown(self)
	local hostwndManager = XLGetObject("Xunlei.UIEngine.HostWndManager")
	local frameHostWnd2 = hostwndManager:GetHostWnd("MainFrame")
	frameHostWnd2:Destroy()
	os.exit()
end

function OnMainWndSize(self, type_, width, height)
	local objectTree = self:GetBindUIObjectTree()
	local rootObject = objectTree:GetRootObject()
	
	rootObject:SetObjPos(0, 0, width, height)
end