/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


//Shortcut to IanniX Object
function run(_command) 	{
	return iannix.execute(_command);
}
function ask(_category, _label, _variable, _defaultValue) {
	return iannix.ask(_category, _label, _variable, _defaultValue);
}
function title(_title) 	{
	return iannix.meta(_title);
}
function console(_log)	{ 
	return iannix.execute("log " + JSON.stringify(_log, null, 4));
}
function load(_filename) {
	return iannix.load(_filename);
}
function loadJSON(_filename) {
	return JSON.parse(load(_filename));
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
function sin(x) 		{	return Math.sin(x);		}
function sqrt(x) 		{	return Math.sqrt(x);	}
function sq(x)			{	return x*x;				}
function tan(x) 		{	return Math.tan(x);		}
function degrees(value) {	return value * 180. / pi;  }
function radians(value) {	return value * pi / 180.;  }
function round(x, y) 	{
	if(y == undefined)	return Math.round(x);
	else 				return Math.round(x*Math.pow(10, y)) / Math.pow(10, y);
}
function random(low, high) {
	if((low == undefined) || (high == undefined))
		return Math.random();
	else
		return range(Math.random(), low, high);
}

//Useful functions
function constrain(value, min, max) {
	return Math.min(max, Math.max(min, value));
}
function dist(x1, y1, z1, x2, y2, z2) {
	var dx = x2 - x1, dy = y2 - y1, dz = z2 - z1;
	return Math.sqrt(sq(dx) + sq(dy) + sq(dz));
}
function angle(x1, y1, x2, y2) {
	var dx = x2 - x1, dy = y2 - y1, angle = 0;
	if((dx > 0) && (dy >= 0))
	    angle = (Math.atan(dy / dx)) * 180.0 / PI;
	else if((dx <= 0) && (dy > 0))
	    angle = (-Math.atan(dx / dy) + HALF_PI) * 180.0 / PI;
	else if((dx < 0) && (dy <= 0))
	    angle = (Math.atan(dy / dx) + PI) * 180.0 / PI;
	else if((dx >= 0) && (dy < 0))
	    angle = (-Math.atan(dx / dy) + 3 * HALF_PI) * 180.0 / PI;
	return angle;
}
function norm(value, low, high, exp) {
	if((high - low) == 0)
		return 0;
	else
		return linexp((value - low) / (high - low), exp);
}
function range(value, low, high, exp) {
	value = linexp(value, exp);
	return value * (high - low) + low; 
}
function rangeMid(value, low, mid, high, exp) {
	value = linexp(value, exp);
	if(value < 0.5)
		return (value * 2) * (mid - low) + low;
	else
		return (value - .5) * 2 * (high - mid) + mid;
}
function map(value, low1, high1, low2, high2, exp) {
	return range(norm(value, low1, high1, exp), low2, high2);
}

function linexp(value, factor) {
	if((factor == undefined) || (factor == 0))
		return value;
	else
		return (exp(factor * value - factor) - exp(-factor)) / (1 - exp(-factor));
}
