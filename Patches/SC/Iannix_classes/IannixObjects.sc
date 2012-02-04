IannixObject {
	var <type, <parent, <childs, <id, <group, <color, <action; //curve can have childs: cursors
	var activity, position, autosize, <size, lineStyle, <allMessages, colors, textures; //debug: not used by now
	var <netAddress;
//	var waitList,spool; //...
	
	*preNew {|type, parent, id|
		^super.newCopyArgs(type, parent, id).xinit(parent, type, id)
	}
	
	xinit {|p, t, i|
		var family;
		netAddress = p.iannixAddress;
		family = p.objects[(t++"s").asSymbol];
		childs = Set.new; //only used by curve, for cursors assigned to it
		if (i.isNil) 
			{
				if (family.isEmpty.not)
					{i = family.keys.asArray.sort.last+1 }
					{i = parent.idOffsets[(t++"s").asSymbol]}
			}; //automatic indexing
		id = i.asInteger; 
		p.objects[(t++"s").asSymbol][id] = this;
		allMessages = [];

	
	}
	
	send {|autoID=false, messagesProtocol, messagesIP| //possibilitŽ de "forwarder" les messages vers une autre app, et avec un autre protocole...
		var idArg;
		if (autoID.not){idArg = id}{idArg = "auto"};
		netAddress.sendMsg("/iannix/add" +  type, idArg);
		messagesProtocol ?? {messagesProtocol = "osc"};
		messagesIP ?? { messagesIP = parent.scIP };
		this.messages_(\id, messagesProtocol, messageAddr: messagesIP); //default setting of output messages in IanniX
		^this;
	} 
	
	position_ {|x=0, y=0, z=0|
		netAddress.sendMsg("/iannix/setPos", id, x.asFloat, y.asFloat, z.asFloat)
		^this;
	}
	
	group_ { |groupName|
		if (groupName.notNil)
			{	groupName = groupName.asSymbol;
 				if (groupName != this.group)
					{ if (this.group.notNil)
						{ parent.groups[this.group].remove(this)};
						parent.groups[groupName] ?? { parent.groups[groupName] = Set.new };
						parent.groups[groupName].add ( this)};
					group = groupName;
					netAddress.sendMsg("/iannix/setGroup", id, groupName);
			}
			{"group needs a name".warn} ; 
					
			//group as Set, to make sure there will only be one instance of this object in the group
		
		^this;
	}
	
	active {|bool=true|
		netAddress.sendMsg("/iannix/setActive", id, if (bool){1}{0} )
		^this;
	}

	autosize {|bool=true|
		netAddress.sendMsg("/iannix/autosize", id, if (bool){1}{0} )
		^this;
	}

	
	size_ {|size|
		netAddress.sendMsg("/iannix/setSize", id, size)
		^this;
	}	

	
	thickness_ {|thickness=1|
		netAddress.sendMsg("/iannix/setThickness", id, thickness)
		^this;
	}
	
	action_ {|function|
		action = function;
		^this;
	}
	
	color_ {|colorObject, state=\active|
		var messaging="Message";
		state = state.asString;
		state = state.first.toUpper++state[1..];
		if ((allMessages.size== 0) || (this.type != \trigger)) {messaging=""};
			
		netAddress.sendMsg("/iannix/setColor"++state++messaging, id, 
			(colorObject.red*255).asInteger, (colorObject.green*255).asInteger, (colorObject.blue*255).asInteger, (colorObject.alpha*255).asInteger
		);
		^this;
	}
	
	lineStyle_{| pattern, factor=1 | 
		//pattern as openGl patterns (16bit hex, or binary, like 2r1111110011110000)
		// http://fly.cc.fer.hr/~unreal/theredbook/chapter02.html, look at "Stippled Lines"
		pattern  = pattern ? 0xFFFF;
		netAddress.sendMsg("/iannix/setLine", id, pattern, factor)
	}
	
	label_{|text|
		netAddress.sendMsg("/iannix/setLabel", id, text)
	}
		
	
	remove {  
		childs.do {| cursor | cursor.remove }; //only relevant for curves
		netAddress.sendMsg("/iannix/remove", id);	
		parent.objects[(type++"s").asSymbol][id] = nil;		parent.objects[(type++"s").asSymbol].removeAt(id);
		(type.asString + id + "removed").inform;
		
	}
	
	messages_ {|messages, protocol="osc", messageAddr="127.0.0.1", port, cmdName|
		var str = ",";
		allMessages = allMessages.add(messages); 
		str = str + protocol++":\/\/";
		cmdName ?? { cmdName = type } ; // type of this object
		port ?? { port = NetAddr.langPort };
		case {protocol=="osc"}
			{  str = str ++ messageAddr ++":"++port++"\/"++cmdName+ type.asString++"_id"; } //first mendatory element in the message 
			{protocol=="midi"}
			{ str = str  ++"IanniX_Out\/"++cmdName };
		if ((messages.isNil) || (messages == \id)) {messages = [""]};
		messages.do {|val| str = str + val.asString };
		netAddress.sendMsg("/iannix/setMessage", id, parent.messagePeriods[type], str);
		^this;
	}
	

}






IannixTrigger : IannixObject {
	var <x, <y, <z, <value=127;
	var <action;

	*new {|parent, id|
		^super.preNew(\trigger, parent, id)
	}
	


	triggerOff_ {|delay|
		netAddress.sendMsg("/iannix/setTriggerOff", id, delay * 0.001);
		^this;
	}

}
	

	
IannixCursor : IannixObject {

	*new {|parent, id|
		^super.preNew(\cursor, parent, id);
	}
	
	putOnCurve {|curve|
		netAddress.sendMsg("/iannix/setCurve", id , curve.id);
		^this;	
	}
	
	width_ {|width=0.1|
		netAddress.sendMsg("/iannix/setWidth", id,  width);
		^this;	
	}
	
	speed_ {|factor=1|
		netAddress.sendMsg("/iannix/setSpeed", id, factor);
		^this;
	}
	
	duration_ {|duration=1|
		netAddress.sendMsg("/iannix/setSpeed", id, "auto", duration);
		^this;
	}
	
	masterSpeed {|factor=1| //? seems like setSpeed to me... 
		netAddress.sendMsg("/iannix/setSpeedF", id, factor);
		^this;
	}
	
	loopPattern_ {|list| //array of speeds, negatives ones for reverse, 0 for stop
		var pattern = "";
		list ?? {list = [1]};
		list.do { |item| pattern = pattern + item };
		netAddress.sendMsg("/iannix/setPattern", id, 0, 0, pattern);
		^this;
	}
	
	offset_ {|initialPoint=0, startPoint=0, endPoint="end"| //endPoint="end", if you don't know the length of the associated curve 
		netAddress.sendMsg("/iannix/setOffset", id, initialPoint, startPoint, endPoint);
		^this;
	}
	
	timePos_ {|pos=0| //in seconds
		netAddress.sendMsg("/iannix/setTime", id, pos);
		^this;
		
	}
	

	
	mapping_ {|outputBoundaries, inputBondaries | 
		//four values = rectangle : x-top-left-corner, y-top-left-corner, x-bottom-right-corner, y-bottom-right-corner
		var outStr = "", inStr = "";
		outputBoundaries !? {
			outputBoundaries.do {|val| outStr = outStr+val };
			netAddress.sendMsg("/iannix/setBoundsTarget", id, outStr);
			
		};
		inputBondaries !? { 
			inputBondaries.do {|val| inStr = inStr+val };
			netAddress.sendMsg("/iannix/setBoundsSource", id, inStr)
		};
		^this;
	}
		

	
}

IannixCurve : IannixObject {
	var shape;
	
	*new {|parent, id|
		^super.preNew(\curve, parent, id)
	}
	

	points_ {|pointsArray| //beziers: 4 or 6 values = start tangent x y (z), end tangent x y (z) 
		var dim;
		pointsArray.do {|pt, i| 
			var ptStr = "", bzStr = "";//,  x, y, z;
			case 
				{pt.isKindOf(Point)}
//					{x = pt.x; y = pt.y; } //z = 0
					{[pt.x, pt.y].do {|p| ptStr = ptStr + p }}
				{pt.any {| elem| elem.isKindOf(Collection) }} // includes beziers: [[x, y , (z)], [beziers]]
					{ pt[0].do {|p| ptStr = ptStr + p };  pt[1].do {|item| bzStr = bzStr + item }}
				{pt.every {| elem | elem.isKindOf(Number)}}      
				{ pt.do {|p| ptStr = ptStr + p } }; //point as flat Array: [x, y, (z)]
			netAddress.sendMsg("/iannix/setPointAt", id, i, ptStr, bzStr );
		};
		^this;	
			
		
	}
	
	fromSVGpath {|svgPath, width, height| 
		netAddress.sendMsg("/iannix/setPointsSVG", id, width, height, svgPath);
		^this;
	}//debug, to be tested
	
	fromSVGpath2 {|svgPath, scale=1| 
		var str = "";
		svgPath.do {|item|
			var x, y;
			if (item.isKindOf(Point))
				{ #x, y = [item.x, item.y]}
				{#x, y = item};
			str = str+ x ++","++y;
		};
		netAddress.sendMsg("/iannix/setPointsSVG2", id, scale, str);
		^this;
	}//ok	
	
	asEllipse {|width=1, height=1|
		netAddress.sendMsg("/iannix/setPointsEllipse", id, width, height);
		^this;
	}

	fromText{|text,  scale=0.1, fontFamily="Arial" | 
		netAddress.sendMsg("/iannix/setPointsTxt", id, scale, fontFamily, text);
		^this;
	}

	fromImage {	|imagePath, scale=1 |
		netAddress.sendMsg("/iannix/setPointsImg", id, scale, imagePath);
		^this;
	}
	
	width_ {|width=0.1|
		netAddress.sendMsg("/iannix/setSize", id,  width);
		^this;	
	}
		
		

} 

