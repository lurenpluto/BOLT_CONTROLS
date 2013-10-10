-- -- This is provided by user
function GetItemFactory()
	local callbackTable = {}
	local userdata = nil
	callbackTable.CreateObject = CreateObject
	callbackTable.GetRowHeight = GetRowHeight
	callbackTable.GetColumnWidth = GetColumnWidth
	-- callbackTable.SetItemPos2 = SetItemPos2
	callbackTable.SetItemData = SetItemData
	return userdata, callbackTable
end

function SetItemPos2(userdata, itemObj, left, top, width, height)
	itemObj:SetObjPos2(left, top, width, height)
end

function GetRowHeight(userdata)
	return 50
end

function GetColumnWidth(userdata, column, widthInAll)
	if column == 1 then
		return 50
	elseif column == 2 then
		return 150
	elseif column == 3 then
		return 150
	end
end

function SetItemData(userdata, itemObj, data, row, column)
	if data == nil then return end
	if itemObj:GetClass() == "TextObject" then
		itemObj:SetText(data)
	elseif itemObj:GetClass() == "ImageObject" then
		itemObj:SetBitmap(data)
	end
end

function CreateObject(userData, column)
	local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
	if column == 2 or column == 3 then
		local itemObj = objFactory:CreateUIObject(nil,"TextObject")
		itemObj:SetVAlign("center")
		itemObj:SetMultiline(true)
		if column == 3 then
			itemObj:SetTextColor("#0000ff")
		end
		return itemObj
	elseif column == 1 then
		local itemObj = objFactory:CreateUIObject(nil, "ImageObject")
		return itemObj
	end
end