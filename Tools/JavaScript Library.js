/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//Shortcut to IanniX Object
function run(_command) 	{	return iannix.execute(_command);		}
function title(_title) 	{	return iannix.meta(_title);				}
function console(_log)	{ 	return iannix.execute('log ' + _log);	}
function ask(_category, _label, _variable, _defaultValue) {
	return iannix.ask(_category, _label, _variable, _defaultValue);
}

//Prototypes for Strings
String.prototype.trim = function()
	{ return (this.replace(/^[\s\xA0]+/, "").replace(/[\s\xA0]+$/, "")) }
String.prototype.startsWith = function(str) 
	{ return (this.match("^"+str)==str) }
String.prototype.endsWith = function(str) 
	{ return (this.match(str+"$")==str) }
String.prototype.replaceAll = function(str, str2)
	{ return (this.replace(new RegExp(str, 'g'), str2)) }
String.prototype.pad = function(length) {
	var str = '' + this;
    while (str.length < length) {
        str = '0' + str;
    }
    return str;
}
   

//Constants
var E          = Math.E;
var LN2        = Math.LN2;
var LN10       = Math.LN10;
var LOG2E      = Math.LOG2E;
var LOG10E     = Math.LOG10E;
var PI         = Math.PI;
var TWO_PI	   = 2 * Math.PI;
var THIRD_PI   = Math.PI / 3;
var QUARTER_PI = Math.PI / 4;
var HALF_PI    = Math.PI / 2;
var SQRT1_2    = Math.SQRT1_2;
var SQRT2      = Math.SQRT2;

//Math functions
function abs(x) 		{	return Math.abs(x);		}
function acos(x) 		{	return Math.acos(x);	}
function asin(x) 		{	return Math.asin(x);	}
function atan(x) 		{	return Math.atan(x);	}
function atan2(x,y) 	{	return Math.atan2(x,y);	}
function ceil(x) 		{	return Math.ceil(x);	}
function cos(x) 		{	return Math.cos(x);		}
function exp(x) 		{	return Math.exp(x);		}
function floor(x) 		{	return Math.floor(x);	}
function log(x) 		{	return Math.log(x);		}
function min(x,y) 		{	return Math.min(x,y);	}
function max(x,y) 		{	return Math.max(x,y);	}
function pow(x,y) 		{	return Math.pow(x,y);	}
function round(x) 		{	return Math.round(x);	}
function sin(x) 		{	return Math.sin(x);		}
function sqrt(x) 		{	return Math.sqrt(x);	}
function sq(x)			{	return x*x;				}
function tan(x) 		{	return Math.tan(x);		}
function degrees(value) {	return value * 180. / pi;  }
function radians(value) {	return value * pi / 180.;  }
function random(low, high) {
	return range(Math.random(), low, high);
}

//Useful functions
function constrain(value, min, max) {
	return Math.min(max, Math.max(min, value));
}
function dist(x1, y1, z1, x2, y2, z2) {
	return Math.sqrt(sq(x1-x2) + sq(y1-y2) + sq(z1-z2));
}
function norm(value, low, high) {
	if((high - low) == 0)
		return low;
	else
		return (value - low) / (high - low);
}
function range(value, low, high) {
	return value * (high - low) + low; 
}
function rangeMid(value, low, mid, high) {
	if(value < 0.5)
		return (value * 2) * (mid - low) + low;
	else
		return (value - .5) * 2 * (high - mid) + mid;
}
function map(value, low1, high1, low2, high2) {
	return range(norm(value, low1, high1), low2, high2);
}


//Plotting functions
function plot(expression) {
	//Extract ranges
	var result  = expression(t);
	var initial = result;
	var step = (initial.t[1] - initial.t[0]) / initial.nbPoints;
	for(var t = initial.t[0] ; t < initial.t[1] ; t += step) {
		//Evaluate expression
		result = expression(t);

		//From spherical to carthesian coords
		if((result.r != undefined) && (result.theta != undefined) && (result.phi != undefined)) {
			result.x = result.r * Math.sin(result.theta) * Math.cos(result.phi);
			result.y = result.r * Math.cos(result.theta);
			result.z = result.r * Math.sin(result.theta) * Math.sin(result.phi);
		}
		
		//Add points
		if((result.x != undefined) && (result.y != undefined) && (result.z != undefined)) {
			result.x += initial.offset.x;
			result.y += initial.offset.y;
			result.z += initial.offset.z;
			iannix.execute('setPointAt current ' + (initial.index++) + ' ' + result.x + ' ' + result.y + ' ' + result.z);
		}
	}
	result.index  = initial.index;
	result.offset = {x: result.x, y: result.y, z: result.z};
	return result;
}
