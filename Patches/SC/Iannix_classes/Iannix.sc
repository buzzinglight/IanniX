Iannix {
	var <responders, <iannixAddress, <scIP, <objects, <>groups, <>globalActions, <>transportActions, transportFunctions, <>idOffsets, <messagePeriods;
	var <speed;
	var <synthGroup, <outGroup, <>mixInputID, <fadeIn, <fadeOut,  <playing, t_warned, c_warned;
	var <debug; //not used for now;
	var <appObjects;
	
	*new { |iannixIP = "127.0.0.1", iannixPort = 1234, sclangIP = "127.0.0.1"|
		^super.new.init(iannixIP, iannixPort, sclangIP);
	}
	
	createDictionaries {
		objects = ( cursors:(), curves:(),triggers:());
		groups = ();
		appObjects = ();
		globalActions  = (
			triggers: {t_warned ?? {"no trigger action defined".warn; t_warned=true}},
			 cursors: {c_warned ?? {"no cursor action defined".warn; c_warned=true}} 
		);
		responders = ();
		transportFunctions = ();
		playing = false;
		[\play, \stop, \fastrewind].do {|message| transportFunctions[message] = {("iannix: " + message).inform; transportActions[message].value } };
		transportActions = (
			\play: {if (playing.not)  { synthGroup !? {synthGroup.run(true); outGroup.set(\trigFade, 1.0) } }; playing = true }, 
			\stop: {synthGroup !? { outGroup.set(\trigFade, 0.0); {fadeOut.wait; if (playing.not) {synthGroup !? { synthGroup.run(false) } } }.fork }; playing = false } 
		);
		transportActions.put(\fastrewind, transportActions[\stop]);
		idOffsets = (\triggers: 2000, \curves: 1000, \cursors: 0);
		messagePeriods = (\trigger: 1, \cursor: 20)
	}
	
	init {|ip, iannixPort, sclangIP|
		scIP = sclangIP;
		this.createDictionaries;
		speed = 1;
		fadeIn = 0.1;
		fadeOut = 0.1;
		this.connect(ip, iannixPort);
	}
	
	connect  {|ip = "127.0.0.1", port = 1234|
		iannixAddress !? {iannixAddress.disconnect};
		iannixAddress = NetAddr(ip, port);
		this.listen(\transport);
		this.fastrewind; //debug, to be evaluated
//		^this;
	
	}
	
	info {
		if (appObjects[\triggers].isNil)
			{ "you must perform any transport action to get info on existing objects in Iannix application".inform;}
			{
				"Existing objects in Iannix application: ".postln;
				["trigger", "cursor", "curve"].do {| objType |
					var sufx="", nb;
					nb  = appObjects[(objType++"s").asSymbol];
					if ( nb > 0)
						{ if (nb > 1) { sufx = "s" }; Post << "\t" << nb << " " << objType << sufx << ".\n" }
						{ Post << "\tno " << objType << ".\n" }
				}
			}

		
	}
	listen{ |type = \triggers, on = true|
			var typeMsg, oscPrefix, removeMsg, message, object, objectID, action, cutS;
			removeMsg = (type.asString + "Responder Removed");
	
		    responders[type] !? {responders[type].remove;  };
		    if (on) {
		    typeMsg = type.asString;
		    if (type != \transport) {typeMsg = typeMsg[..typeMsg.size-2]};//truncating ending 's'
		    oscPrefix = ("\/"++typeMsg).asSymbol;
		    ("Iannix: listening to" + type++"...").inform;
			responders[type] = OSCresponderNode(iannixAddress, oscPrefix, { | time, responder, msg | 

				message = [msg[1].asInteger] ++ msg[2..]; //objectID as Integer
				if (oscPrefix != '/transport' )
				{
					objectID = message.first;
					object = objects[type][objectID];
					object ?? { object = IannixObject.preNew(typeMsg, this, objectID) };
					
					action = object.action ? globalActions[type];
					action.(message);
				}
				{
					[\triggers, \cursors, \curves].do {|objType, i| appObjects[objType] = msg[i+2] };
					transportFunctions[msg[1]].value;

				}
			}).add;
		    }{ removeMsg.inform };
		this.add2cmdPeriod({ responders[type].remove; removeMsg.inform; this.stop});
		^this;

	}
	
	removeResponders {
		responders.do {|resp| resp.remove };
		responders = ();
		"Iannix responders removed".inform;
	}
	
	remove {|target| //object or group name
		case 
			{ target.isKindOf(IannixObject)}{ target.remove } 
			{ target.isKindOf(String)}{
				target = target.asSymbol;
				if (this.groups[target].notNil) { 
					this.groups[target].do {| object | object.remove };
					this.groups.removeAt(target);
					iannixAddress.sendMsg("/iannix/remove", target);
				}
			}
	}
					
					
					
		
	removeAll {|total=false| //if total, remove all objects in Iannix.app ( even  objects not created from sc )
		if (total) {iannixAddress.sendMsg("/iannix/clear") };
		this.removeResponders;
		this.createDictionaries;
		this.freeSynths;
				
	}
	
	freeSynths {
		synthGroup !? { synthGroup.free; synthGroup = nil }; "synthGroup removed".inform;
		outGroup !? { outGroup.free ; outGroup = nil }; "outGroup removed".inform;
	}
	
	
	clear {
		this.removeAll(true);
	}
	
	resetScore {|zoom=100, total=false| //remove local representations of iannix objects, and responders (and even  objects not created from sc, if total ==  true)
		objects.do {|dict| dict.do {|innerObject| innerObject.remove} }; //objects in Iannix.app
		this.zoom(zoom);
		this.removeAll(total);
		{0.1.wait;this.listen(\transport)}.fork;
		this.rotate;
		
	}
	
	rotate {|x=0, y=0, z=0|
		iannixAddress.sendMsg("/iannix/rotate", x, y, z);
	}
	
	createSynthGroup {|server|
		server ?? { server = Server.default };
		server.waitForBoot ({
			var id;
			mixInputID = server.options.numOutputBusChannels + server.options.numInputBusChannels;
			SynthDef(\iannixFade, {|in=0, trigFade = 1.0, fadeIn=0.1, fadeOut = 0.1|
				var input; 
				input = In.ar(in, 2) * EnvGen.kr(Env.asr(fadeIn, 1, fadeOut, curve: [2, -2]), gate: trigFade);
				Out.ar(0, input); 
			
			}).send(server);
			synthGroup ?? {synthGroup = Group.new};
			("Iannix: new synth group created ("++ synthGroup.nodeID ++"). transport actions operate on it (run true, false)").inform;
			synthGroup.run(false);
			synthGroup.set("out", mixInputID);
			outGroup =  Group(synthGroup, \addAfter);
			("Iannix: general out group created ("++ outGroup.nodeID ++"). Please put a \"out\" argument to your SynthDef\(s\) if you want fadeTime control on play\/stop").inform;
			server.sendBundle(0.2, ["/s_new", "iannixFade", id = server.nextNodeID, 0, outGroup.nodeID], ["/n_set", id, "fadeIn", fadeIn, "fadeOut", fadeOut, "in", mixInputID]);
		});
		this.add2cmdPeriod({ 
			this.freeSynths;
		});
		^this;
		
	}
	
	add2cmdPeriod { | func |
		CmdPeriod.add(func);
	}

	//transport 
	
	play {|speed|
		speed !? {this.speed = speed};
		iannixAddress.sendMsg("/iannix/play", this.speed);
		transportFunctions[\play].value;
	}
	stop {
		iannixAddress.sendMsg("/iannix/stop");
		transportFunctions[\stop].value;
	}
	fastrewind {
		iannixAddress.sendMsg("/iannix/fastrewind");
		transportFunctions[\fastrewind].value;
	}
	
	speed_ {|value=1|
		iannixAddress.sendMsg("/iannix/speed", value);
		speed = value;
	}
	
	//general commands
	
	zoom {|value=100|
		iannixAddress.sendMsg("/iannix/zoom", value);
	}
	
	center {|x=0, y=0|
		iannixAddress.sendMsg("/iannix/center", x, y);
	}
		
	//objects
	
	/* 
	(useful for mirroring the existing iannix.app objects, until iannix team implement a dump message for us)
	//put send=false to register (in sc)  any object already existing in IanniX.app
	*/
	
	triggers {
		^this.objects[\triggers];
	}
	
	curves {
		^this.objects[\curves];
	}
	
	cursors {
		^this.objects[\cursors];
	}

	//creation
	trigger {| xPos=0, yPos=0, zPos=0, send = true | 
		var trg;
		trg = IannixTrigger(this);
		if (send) { trg.send; trg.position_(xPos, yPos, zPos) };
		^trg;
	}
	
	curve {|pointsArray, xPos=0, yPos=0, zPos=0, send = true| //if pointsArray, a curve is added in Iannix
		var crv;
		crv = IannixCurve(this);
		if (send) { 
			crv.send;
			crv.points_(pointsArray);
			crv.position_(xPos, yPos, zPos) ;
		};		
		^crv;
	}

	cursor {|curve, send = true |
		var crs;
		crs = IannixCursor(this);
		if (send) {
			crs.send;
			curve !? {crs.putOnCurve(curve)}
			};
			curve !? {curve.childs.add(crs)}; //useful when deleting a curve
		^crs;
	}
	
	activate {|groupName, bool=true|
		groupName ?? { groupName = "all" };
		iannixAddress.sendMsg("/iannix/setActive", groupName, if (bool){1}{0} )
	}
	
	fadeTime_ {|in=0.1, out|
		fadeIn = in;
		synthGroup.set("out", mixInputID);
		out ?? {out = in};
		fadeOut = out;
		outGroup !? { outGroup.set(\fadeIn, in, \fadeOut, out) };
	}
	
//	debug { |flag= true| 
//		if (flag ) {debug = true} }
		
}