function OnInitControl(self)
	self:GetAttribute().SectionList = {}
	self:GetAttribute().SectionWidthList = {}
	self:GetAttribute().SectionNameList={}
	self:SetLimitChild(true)
	self:GetControlObject("header.layout"):SetLimitChild(true)
end

function GetScrollPos(self)
	if self:GetAttribute().ScrollPos ==  nil then
		self:GetAttribute().ScrollPos = 0
	end
	return self:GetAttribute().ScrollPos
end

function SetScrollPos(self, pos)
	self:GetAttribute().ScrollPos = pos
	local l,t,r,b = self:GetControlObject("header.layout"):GetObjPos()
	self:GetControlObject("header.layout"):SetObjPos(0-pos, 0, r-l-pos, b-t)
end

function GetSectionWidthList(self)
	return self:GetAttribute().SectionWidthList
end

function SetSectionWidthList(self, widthTable)
	self:GetAttribute().SectionWidthList = widthTable
	local sectionList = self:GetAttribute().SectionList
	local l,t,r,b = self:GetObjPos()
	b = b-t
	l,t,r = 0,0,0
	for i=1,table.maxn(widthTable) do
		if sectionList[i] ==  nil then
			sectionList[i] = createSection(self, i)
			self:GetControlObject("header.layout"):AddChild(sectionList[i])
		end
		r = l+widthTable[i]
		sectionList[i]:SetObjPos(l,t,r,b)
		l = r
	end
	self:GetControlObject("header.layout"):SetObjPos(0, 0, r, b)
end

function SetSectionNameList(self, nameList)
	self:GetAttribute().SectionNameList=nameList
	local sectionList = self:GetAttribute().SectionList
	for i=1,table.maxn(nameList) do
		if sectionList[i] == nil then
			sectionList[i]=createSection(self,i)
			self:GetControlObject("header.layout"):AddChild(sectionList[i])
		end
		sectionList[i]:SetText(nameList[i])
	end
end

function createSection(self, idx)
	local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
	local textObj = objFactory:CreateUIObject("btn"..idx, "ListView.Header.Section")
	return textObj
end