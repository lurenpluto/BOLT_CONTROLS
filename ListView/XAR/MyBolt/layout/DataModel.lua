-- 如果用户设置了datamodel callbackTable和userdata, 就用 ListView.Attribute.ItemDataTable作为缓存区.
-- 如果用户调用SetDataTable, 直接赋值给ItemDataTable, 就用 ListView.Attribute.ItemDataTable存储所有数据, 不再动态加载数据

function SetDataModel(self, userdata, callbackTable)
	local attr = self:GetAttribute()
	attr.dataModelUserData = userdata
	attr.dataModelCallbackTable = callbackTable
	attr.ItemDataTable = {}
	
	if attr.dataModelCallbackTable.GetColumnCount == nil then
		Warn("No GetColumnCount method provided, by default return 1")
		attr.dataModelCallbackTable.GetColumnCount = 
			function(userdata)
				return 1
			end
	end
	
	local expectedMethods = { 	"GetCount",	
								"GetItemAtIndex",
								"GetColumnCount"}
	
	local checkResult = CheckMethodWithAlert(expectedMethods, attr.dataModelCallbackTable, "dataModel")
	
	if attr.dataModelCallbackTable.GetColumnNameList == nil then
		local function dummyFunGetColumnNameList(userdata)
			local nameList = {}
			local colCount = self:GetColumnCount()
			for i=1,colCount do
				nameList[i]="section "..i
			end
			return nameList
		end
		attr.dataModelCallbackTable.GetColumnNameList = dummyFunGetColumnNameList
	end
	
	local preloadDataCount = attr.PreloadDataCount
	
	-- 如果用户提供SetDataBatchReadyListener, 优先用DataBatchReadyListener
	-- 如果没有提供, 再用SingleDataReadyListener
	-- 如果都没有提供, 但是设置了Preload>0,那就看不到数据了
	-- 当ListView收到DataModel的DataBatchReady的回调的时候
	-- 如果DataModel提供了GetDataBatch方法返回, ListView调用该方法更新数据
	-- 如果没有提供, ListView调用GetItemAtIndex
	if attr.dataModelCallbackTable.SetDataBatchReadyListener then
		local function funOnDataBatchReady(from, to)
			-- 如果反复加载释放数据, 可能此处Ready的Data实际上已经被释放了
			if from < attr.PreloadFrom then from = attr.PreloadFrom end
			if to > attr.PreloadTo then to = attr.PreloadTo end
			if from~=nil and to and from < to then
				if attr.dataModelCallbackTable.GetDataBatch then
					local funGetDataBatch = attr.dataModelCallbackTable.GetDataBatch
					local funSetItemData = attr.itemFactoryCallbackTable.SetItemData
					-- GetDataBatch返回一个以row, column为索引的二维数组
					local dataBatch = funGetDataBatch(attr.dataModelUserData, from, to)
					for row, rowTable in pairs(dataBatch) do
						if type(rowTable) ~= "table" then Warn("row table is not table") 
						else
							for column, itemData in pairs(rowTable) do
								local itemObj = self:GetAttribute().PrivateMethods.getVisibleItemObject(self, row, column)
								attr.ItemDataTable[row][column] = itemData
								if itemData and itemObj then
									funSetItemData(attr.itemFactoryUserData, itemObj, itemData, row, column)
								end -- valid itemdata
							end -- for column
						end -- if rowTable type is table
					end -- for row, rowTable
				else
					local funGetItemAtIndex=attr.dataModelCallbackTable.GetItemAtIndex
					local funSetItemData = attr.itemFactoryCallbackTable.SetItemData
					for row=from,to do
						for col=1,self:GetColumnCount() do
							local itemData = funGetItemAtIndex(attr.dataModelUserData, row, col)
							self:GetAttribute().ItemDataTable[row][col] = itemData
							local itemObj = self:GetAttribute().PrivateMethods.getVisibleItemObject(self, row, col)
							if itemObj and itemData then
								funSetItemData(attr.itemFactoryUserData, itemObj, itemData, row, col)
							end -- if ItemObj and itemData
						end -- for column
					end -- for row=from,to
				end -- valid GetDataBatch
			end -- if from and to
		end -- funOnDataBatchReady
		attr.dataModelCallbackTable.SetDataBatchReadyListener(attr.dataModelUserData, funOnDataBatchReady)
	elseif attr.dataModelCallbackTable.SetSingleDataReadyListener then
		local function funOnDataReady(row, column)
			if attr.PreloadFrom<=row and attr.PreloadTo>=row and column then
				local funGetItemAtIndex = attr.dataModelCallbackTable["GetItemAtIndex"]
				local itemData = funGetItemAtIndex(attr.dataModelUserData, row, column)
				self:GetAttribute().ItemDataTable[row][column] = itemData
				local itemObj = self:GetAttribute().PrivateMethods.getVisibleItemObject(self, row, column)
				if itemObj and itemData then
					local funSetItemData = self:GetAttribute().itemFactoryCallbackTable.SetItemData
					funSetItemData(self:GetAttribute().itemFactoryUserData, itemObj, itemData, row, column)
				end -- if itemObj
			end -- if row!=nil and column~=nil
		end -- OnDataReady
		attr.dataModelCallbackTable.SetSingleDataReadyListener(
			attr.dataModelUserData, funOnDataReady)
	end -- if SetDataReadyListener
	
	if attr.PreloadDataCount > 0 then
		if attr.PreloadDataCount < attr.ScrollAttributes.Capacity*2 then
			attr.PreloadDataCount = attr.ScrollAttributes.Capacity*2
		end
		attr.PreloadFrom = -1
		attr.PreloadTo = -1
		prepare(self, 0, preloadDataCount-1)
	end
	
	if attr.dataModelCallbackTable.SetDataChangeListener then	
		function onDataChanged(from, to)
			self:FireExtEvent("DataChanged")
			if attr.PreloadDataCount > 0 then
				local intersectionFrom = math.max(from, attr.PreloadFrom)
				local intersectionTo = math.min(to, attr.PreloadTo)
				if intersectionFrom <=intersectionTo then 
					releaseDataClip(self, intersectionFrom, intersectionTo)
					preloadDataClip(self, intersectionFrom, intersectionTo)
				end
			end
			self:UpdateItems()
		end
		attr.dataModelCallbackTable.SetDataChangeListener(attr.dataModelUserData, onDataChanged)
	end
end

-- 如果用户提供了PrepareData方法, 就调用PrepareData方法加载数据, 如果没有提供, 就直接调用GetItemAtIndex
-- 如果用户提供了ReleaseData方法, 就调用ReleaseData方法在不再需要的时候释放数据, 如果没有提供, 就什么都不做

function releaseDataClip(self, from, to)
	local attr = self:GetAttribute()
	local funReleaseData = attr.dataModelCallbackTable["ReleaseData"]
	for row=from, to do
		attr.ItemDataTable[row] = nil
	end
	if funReleaseData ~= nil then
		funReleaseData(attr.dataModelUserData, attr.PreloadFrom, from-1)
	end
end

function preloadDataClip(self, from, to)
	local attr = self:GetAttribute()
	local funGetItemAtIndex = attr.dataModelCallbackTable["GetItemAtIndex"]
	local funPrepareData = attr.dataModelCallbackTable["PrepareData"]
	local colCount = self:GetColumnCount()
	if funPrepareData ~= nil then
		for row=from, to do
			attr.ItemDataTable[row] = {}
		end
		funPrepareData(attr.dataModelUserData, from, to)
	else
		for row=from,to do
			attr.ItemDataTable[row] = {}
			for col=1,colCount do
				attr.ItemDataTable[row][col] = funGetItemAtIndex(attr.dataModelUserData, row, col)
			end
		end
	end
end

function prepare(self, from, to)
	if from <= 1 then from = 1 end
	if to >= self:GetRowCount() then to = self:GetRowCount() end
	local attr = self:GetAttribute()
	local funGetItemAtIndex = attr.dataModelCallbackTable["GetItemAtIndex"]
	local funPrepareData = attr.dataModelCallbackTable["PrepareData"]
	local funReleaseData = attr.dataModelCallbackTable["ReleaseData"]
	
	if attr.PreloadFrom ~= nil and attr.PreloadFrom < from then
		releaseDataClip(self, attr.PreloadFrom, from-1)
	end

	if attr.PreloadFrom ~= nil and attr.PreloadFrom > from then
		preloadDataClip(self, from, attr.PreloadFrom-1)
	end
	
	if attr.PreloadTo ~= nil and attr.PreloadTo > to then
		releaseDataClip(self, to+1, attr.PreloadTo)
	end
	if attr.PreloadTo ~= nil and attr.PreloadTo < to then
		preloadDataClip(self, attr.PreloadTo+1, to)
	end
	attr.PreloadFrom = from
	attr.PreloadTo = to
end

function SetDataTable(self, dataTable)
	self:SetScrollPosV(0)
	local attr = self:GetAttribute()
	attr.dataModelUserData = nil
	attr.dataModelCallbackTable = nil
	attr.ItemDataTable = dataTable
	onColumnCountChange(self, self:GetColumnCount())
	onRowCountChange(self, self:GetRowCount())
end

function GetItemDataTable(self)
	local attr = self:GetAttribute()
	if attr.ItemDataTable == nil then
		attr.ItemDataTable = {{}}
	end
	return attr.ItemDataTable
end

function GetColumnCount(self)
	local attr = self:GetAttribute()
	if attr.dataModelCallbackTable then
		local colCount = 4
		local colCountFunction = attr.dataModelCallbackTable.GetColumnCount
			if colCountFunction then
				colCount = colCountFunction(attr.dataModelUserData)
			end
		return colCount
	else
		local itemDataTable = self:GetItemDataTable()
		return table.maxn(itemDataTable[1])
	end
end

function GetRowCount(self)
	local attr = self:GetAttribute()
	if attr.dataModelCallbackTable then
		local rowCount = 0
		local rowCountFunction = attr.dataModelCallbackTable["GetCount"]
			if rowCountFunction then
				rowCount = rowCountFunction(attr.dataModelUserData)
			end
		return rowCount
	else
		local itemDataTable = self:GetItemDataTable()
		return table.maxn(itemDataTable)
	end
end

function GetItemAtIndex(self, row, column)
	if row > self:GetRowCount() or column > self:GetColumnCount() then return nil end
	local attr = self:GetAttribute()
	if attr.dataModelCallbackTable then
	-- 先看看有没有在预加载的table里, 如果在的话直接返回, 如果不在的话, 就加载preloadDataCount个.
		local item = nil
		if attr.PreloadDataCount > 0 then
			if attr.ItemDataTable[row] == nil then
				local from = row-attr.PreloadDataCount/2>0 and math.ceil(row-attr.PreloadDataCount/2) or 0
				local to = from + attr.PreloadDataCount-1
				prepare(self, from, to)
			end
			local itemRow = attr.ItemDataTable[row]
			if itemRow ~= nil then item = itemRow[column] end
			if item == nil then item = "loading~" end
		else
			local funGetItemAtIndex = attr.dataModelCallbackTable["GetItemAtIndex"]
			item = funGetItemAtIndex(attr.dataModelUserData, row, column)
		end
		return item
	else
		local itemDataTable = self:GetItemDataTable()
		local rowTable = itemDataTable[row]
		if rowTable == nil then return nil 
		else return rowTable[column] end
	end
end

function SetItemDataAtIndex(self, itemData, row, column)
	local attr = self:GetAttribute()
	if attr.dataModelCallbackTable then
		if attr.dataModelCallbackTable.SetItemDataAtIndex ~= nil then
			local funSetData = attr.dataModelCallbackTable.SetItemDataAtIndex
			funSetData(attr.dataModelUserData, itemData, row, column)
		end
	else
		local itemDataTable = self:GetItemDataTable()
		if self:GetItemDataTable()[row] == nil then self:GetItemDataTable()[row] = {} end
		table.insert (self:GetItemDataTable()[row], column, itemData)
	end
end

function SetColumnNameList(self, nameList)
	local attr = self:GetAttribute()
	local callbackTable = attr.dataModelCallbackTable
	-- 为什么要在局部函数里再定义局部函数
	-- funSetColumnNameList的目的:只有当用户调用到SetColumnNameList时,才会检查用户有没有提供SetColumnNameList,才会有可能实例化这个函数
	-- callbackTable.GetColumnNameList的目的:用户可能已经提供过GetColumnNameList了,在此重复定义会改变GetColumnNameList的行为,但是既然用户不提供SetColumnNameList还要调它而且是在提供ItemFactoryCallbackTable之后,我们认为用户想要用SetColumnNameList覆盖之前提供的GetColumnNameList,所以重新定义GetColumnNameList返回用户刚刚通过SetColumnNameList传给DataModel的值. 如果用户稍后想恢复最早定义的GetColumnNameList的行为,可以通过再次SetItemFactory来达到目的
	if callbackTable~=nil then
		local funSetColumnNameList = callbackTable.SetColumnNameList
		if funSetColumnNameList==nil then
			funSetColumnNameList = function (userdata, funArgNameList)
				callbackTable.GetColumnNameList = function(userdata)
					return funArgNameList
				end
			end
			callbackTable.SetColumnNameList = funSetColumnNameList
		end
		funSetColumnNameList(attr.dataModelUserData, nameList)
	else
		self:GetAttribute().ItemDataHeader = nameList
	end
end

function GetColumnNameList(self)
	if self:GetAttribute().dataModelCallbackTable then
		return self:GetAttribute().dataModelCallbackTable.GetColumnNameList(self:GetAttribute().dataModelUserData)
	else
		if self:GetAttribute().ItemDataHeader == nil then
			self:GetAttribute().ItemDataHeader = {}
		end
		return self:GetAttribute().ItemDataHeader
	end
end