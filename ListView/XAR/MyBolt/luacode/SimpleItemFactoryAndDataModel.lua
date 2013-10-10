local operation = {}

function GetTextItemFactory()
	local callbackTable = {}
	local userdata = nil
	callbackTable.CreateObject = 
		function (userdata, column)
			local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
			if column == 1 then 
				local button = objFactory:CreateUIObject(nil,"BaseUI.Button")
				local cookie, ret = button:AttachListener("OnClick", true, OnButtonClicked)
				return button
			else return objFactory:CreateUIObject(nil,"TextObject") end
		end
	callbackTable.GetRowHeight = 
		function (userdata)
			return 50
		end
	callbackTable.GetColumnWidth = 
		function (userdata, column, widthInAll)
			if column == 1 then return 50 end
			if column == 2 then return 250 end
		end
	callbackTable.SetItemData = 
		function(userdata, itemObj, data, row, column)
			if itemObj == nil then return end
			if data ~= nil then
				itemObj:SetText(data)
				if column == 1 then
					itemObj:GetAttribute().row = row
					itemObj:GetAttribute().column = column
				end
			end
		end
	callbackTable.SetItemPos2 = 
		function (userdata, itemObj, left, top, width, height)
			if itemObj~=nil and itemObj:GetClass()=="BaseUI.Button" then
				itemObj:SetObjPos2(left+10, top, 30, 30)
				end
			if itemObj~=nil and itemObj:GetClass()=="TextObject" then
				itemObj:SetObjPos2(left, top, width, height) end
		end
	return userdata, callbackTable
end

function OnButtonClicked(button)
	if button:GetClass() == "BaseUI.Button" then
		local opr = button:GetText()
		local row = button:GetAttribute().row
		if opr == "加" then
			operation.Add(row, "变", os.date())
		elseif opr == "减" then
			operation.Sub(row)
		elseif opr == "变" then
			operation.Change(row, "减", os.date())
		end
	end
end

function GetSimpleDataModelObject()
	local dataTable = {{"加", os.date()}}
	local callbackTable = {}
	callbackTable.GetCount = 
		function (userdata)
			return #dataTable
		end
	callbackTable.GetColumnCount=
		function (userdata)
			if dataTable[1] ~= nil then return #(dataTable[1]) 
			else return 1 end
		end
	callbackTable.GetItemAtIndex = 
		function (userdata, row, column)
			if dataTable[row] ~= nil then
				local text = dataTable[row][column]
				return text
			else
				return nil
			end
		end
	callbackTable.SetDataChangeListener = 
		function (userdata, dataChangedListener)
			callbackTable.DataChangeListener = dataChangedListener
		end
	operation.Add = 
		function (row, sign, data)
			local count = #dataTable
			for r=row+1, count+1 do
				dataTable[r] = dataTable[r-1]
			end
			dataTable[row]={sign, data}
			if callbackTable.DataChangeListener ~= nil then
				callbackTable.DataChangeListener(row, count+1)
			end
		end
	
	operation.Sub = 
		function (row)
			local count = #dataTable
			if count > 0 then
				for r=row,count do
					dataTable[r] = dataTable[r+1]
				end
			end
			if callbackTable.DataChangeListener ~= nil then
				callbackTable.DataChangeListener(row, count)
			end
		end
	
	operation.Change = 
		function (row, sign, data)
			local count = #dataTable
			dataTable[row]= {sign, data}
			if callbackTable.DataChangeListener ~= nil then
				callbackTable.DataChangeListener(row, row)
			end
		end
	return nil, callbackTable
end
