local treeModel = {}
-- TreeView method
function createNode(key, data)
	local Node={}
	Node.Key=key
	Node.Children={}
	Node.Data = data
	Node.Expand =false
	return Node
end

function createNodeTreeFromTable(key, nodeTable)
	if nodeTable == nil then return nil end
	if type(nodeTable) == "table" then
		local Node = createNode(key)
		local nodes = {}
		for k,v in pairs(nodeTable) do
			local newKey = key.."."..k
			local node=createNodeTreeFromTable(newKey, v)
			node.Father = Node
			nodes[newKey]=node
		end
		Node.Children = nodes
		Node.Data = key
		return Node
	end
	if type(nodeTable) ~= "table" then
		local Node = createNode(key, key)
		return Node
	end
end

function GetTreeModelFromTable(dataTable)
	local root = createNodeTreeFromTable("", dataTable)
	root.Expand = true
	local i = 1
	for k,v in pairs(root.Children) do
		v.Expand = true
	end
	
	treeModel.GetChildren = 
		function (node)
			return node.Children
		end
	treeModel.HasChildren = 
		function (node)
			for k,v in pairs(node.Children) do
				return true
			end
			return false
		end
	treeModel.GetFather = 
		function (node)
			return node.Father
		end
	treeModel.GetChild = 
		function (node, key)
			return node.Children[key]
		end
	treeModel.GetRoot = 
		function()
			return treeModel.Root
		end
	treeModel.Root = root
	return treeModel
end

function GetDirTreeModel(rootDir)
	if not rootDir then 
		rootDir = ""
	end

	local root = createNode(rootDir, rootDir)
	root.Father = nil
	root.Expand = true
	root.HasChildren = true
	treeModel.Root = root

	local dirFactory = XLGetObject("LuaDir.Factory.Object")
	local dir = dirFactory:CreateInstance()
	
	treeModel.GetChildren = 
		function (Node)
			local curDir = Node.Key
			local subDirs = dir:GetSubDirs(curDir)
			if type(subDirs) ~= "table" then 
				Node.Children = {}
			else
				for k,info in pairs(subDirs) do
					local path = info[2]
					local key = curDir..path
					if string.sub(key, -1, -1) ~= "\\" then
						key = key.."\\"
					end
					local node = Node.Children[key]
					local data ={}
					data.path = path
					data.isDir = info[1]
					if not node then 
						node = createNode(key, data) 
						node.Father = Node
					end
					if info[1] == true then
						node.HasChildren = true
					else node.HasChildren = false end
					Node.Children[key] = node
				end
			end
			return Node.Children
		end

	treeModel.HasChildren = 
		function (node)
			return node.HasChildren
		end
	treeModel.GetFather = 
		function (node)
			return node.Father
		end
	treeModel.GetChild = 
		function (node, key)
			return node.Children[key]
		end
	treeModel.GetRoot = 
		function()
			return treeModel.Root
		end
	return treeModel
end