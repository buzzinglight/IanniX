PianniX {
	var parent, times, values, depths, limit, x, y, z, orientation, shape, color, groupID;
	var count = 0, valStream, depthsStream, line;
	var triggers, traject, cursor;
	
 * new {|parent, times, values = 0, depths = 0, limit = 10, x=0, y=0, z = 0, orientation=\x, shape=\line, color, groupID=0 |
 	^super.newCopyArgs(parent, times, values, depths, limit, x, y, orientation, shape, color, groupID).create(parent, times, values, depths, limit, x, y, z, orientation, shape, color, groupID)
 }
 	create {|parent, times, values, depths, limit, x, y, z, orientation, shape, color, groupID|
		var onsets, c=0, summed=0, stream, trigNb, cursorNb;
		var circle, circ, center, ray, youAreHere = 0;
		onsets = [0];
		triggers = []; 
		times ?? {times = Pseq([1],inf)};
		stream = times.asStream;
		while({onsets.last<=(limit - 1)})
			{summed = summed+stream.next; onsets = onsets.add(summed);  c = c+1 };
			
		valStream = values.asStream;
		depthsStream = depths.asStream;
//		parent.updateInfo;
		trigNb = parent.triggers.size;
		cursorNb = parent.cursors.size;
		if (shape==\line)
		{
			if (orientation==\x) //il y a mieux ˆ faire sans doute...
				 {onsets.do { |tm, j|
				 			var val;
				 			val = valStream.next ? 0;
							count = count+1;
							triggers = triggers.add(parent.trigger(tm+x+0.003, y + (val*0.01), depthsStream.next.postln ? 0, val, color ? Color.blue, cid: count+trigNb, gid: groupID));//cid ˆ calculer par updateInfo
				};
				
				traject=parent.line(x, y, z, limit+x, y, z);
				}
				{
				onsets.do { |tm, j|
							var val;
				 			val = valStream.next ? 0;
							count = count+1;
							triggers = triggers.add(parent.trigger(x + (val*0.01), tm+y+0.003, depthsStream.next ? 0, val ? 0, color ? Color.blue, cid: count+trigNb, gid: groupID));//cid ˆ calculer par updateInfo
				};
				
				traject=parent.line(x, y, z, x, y+limit, z);
				
				};
			cursor = parent.cursor(traject.id, 1, 0.8, 1, 1, cid: cursorNb);//cid ˆ calculer par updateInfo
		}
		{
			circ = limit;
			ray = circ/2pi;
			center = x@y;
			traject = parent.circle(x, y, z, ray);
			cursor = parent.cursor(traject.id, 1, 0.8, 1, 1, cid: cursorNb);//cid ˆ calculer par updateInfo
			
			onsets.do {|tm, j|
				var point;
				count = count+1;
				youAreHere = youAreHere+tm;
				point = this.rotation(center, ray, tm/ray);
				triggers = triggers.add(parent.trigger(point.x, point.y, depthsStream.next ? 0, valStream.next ? 0, color ? Color.blue, cid: count+trigNb, gid: groupID))
			}
		};
		
		parent.patterns = parent.patterns.add(this);
	
	}
	
	speed {|speed|
		cursor.speed_(speed);
	}
	position { |x, y, z|
		var offsetX, offsetY, offsetZ;
		Post << "traj: " << traject << "\n";
		#offsetX, offsetY, offsetZ = [x, y, z] - [traject.x, traject.y, traject.z];
		traject.position_(x, y, z);
		triggers.do {|tr| tr.position_(tr.x+offsetX, tr.y+offsetY, tr.z+offsetZ) };
	}
//private

	rotation { |origin, rd, angle|  
		var sinr, cosr, x_, y_;
		#x_, y_ = [0, rd] ;
		sinr = angle.sin;
		cosr = angle.cos;
		^(((x_ * cosr) - (y_ * sinr)) @ ((y_ * cosr) + (x_ * sinr))) + origin
	}
			 

}