-- 不管传入是table还是control object, 都是table
function CheckMethod(expectedMethodsTable, actualMethodsTable)
	local lackingMethods = {}
	local result = true
	for index, methodName in pairs(expectedMethodsTable) do
		if actualMethodsTable[methodName] == nil then
			table.insert(lackingMethods, methodName)
			result = false
		end
	end
	return result, lackingMethods
end

function CheckMethodWithAlert(expectedMethodsTable, actualMethodsTable, objName)
	local result, lackingMethods = CheckMethod(expectedMethodsTable, actualMethodsTable)
	if result == false then
		local warning = "The object lacks these methods:"
		if objName then 
			warning = objName.." lacks these methods:"
		end
		for k,v in pairs(lackingMethods) do
			warning = warning.." "..v
		end
		Warn(warning)
	end
	return result
end

function RegisterGlobal()
	XLSetGlobal("CheckMethod", CheckMethod)
	XLSetGlobal("CheckMethodWithAlert", CheckMethodWithAlert)
end