p = ProxySpace.push(s.boot);
p.makeTempoClock(120/120)
p.quant = 4;
m = NetAddr("127.0.0.1", 5612); // para OpenFrameworks
m.sendMsg("/camDistance", 7000);


(

OSCdef(\camDistance, {|msg|
	var data = msg[3];
	m.sendMsg("/camDistance", data);
	data.postln;
}, '/camDistanceDef');

~camDistanceSend = {SendReply.kr(Impulse.kr(~tempo*60), '/camDistanceDef', ~camDistance.kr)};
~camDistance = {XLine.kr(7000, 10, 60 * 8)};

// OSCdef(\camDistance).free

)