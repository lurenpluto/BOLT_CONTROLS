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

-- client dataTable Method
function createDataTreeTable()
	local tree={}
	tree.A1 = "A"
	tree.B1 = "B"
	tree.C1 = "C1"
	local subTree = {}
	subTree.C = "C"
	subTree.D = "D"
	tree.E = subTree
	local subTree2 = {}
	subTree2.F = "E"
	subTree2.G = "F"
	subTree.H = subTree2
	tree.C = subTree2
	tree.D = subTree
	local subTree3 = {}
	subTree3.M = subTree2
	subTree3.N = subTree
	tree.subTree3 = subTree3
	return {root=tree}
end

function OnInitTree(tree)
	local path = __document
	local index = string.find(path, "/[^/]*$")
	local layoutDir = string.sub(path,1,index)
	
	local itemDir = layoutDir.."ItemFactory.lua"
	local mdItem = XLLoadModule(itemDir)
	local itemFactory = mdItem.GetCustomItemFactory(tree)
	tree:SetItemFactory(itemFactory)

	local modelDir = layoutDir.."TreeModel.lua"
	local mdModel = XLLoadModule(modelDir)
	local model = mdModel.GetDirTreeModel()
	tree:SetTreeModel(model)
end

function OnTest(layout)
	local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
	
	local line = objFactory:CreateUIObject(nil, "LineObject")
	layout:AddChild(line)
	line:SetVisible(true)
	line:SetLinePenResID("pen.dot")
	line:SetLineColorResID("system.black")
	line:SetObjPos(100,100,1000,1000)
	local l,t,r,b = line:GetAbsPos()
	line:SetLinePoint(0,0,"width","height")
end