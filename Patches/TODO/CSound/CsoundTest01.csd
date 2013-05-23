
; TO USE WITH: CsoundTest01.nxscore

; Simple sine oscillator with frequency drived by the cursor y value; cursor x value
; is mapped to time.

<CsoundSynthesizer>
<CsOptions>
-o dac
</CsOptions>
<CsInstruments>
sr				=					44100
ksmps			=					10
nchnls			=					2
0dbfs			=					1

gihandle		OSCinit		57120

gkValue		init				0

; Listener.
					instr			1

; the received values must be initialized
kcursor_id						init				0
kcursor_xPos					init				0
kcursor_yPos					init				0

nxtmsg:
	kcurs		OSClisten	gihandle, "/cursor", "iff", kcursor_id, kcursor_xPos, kcursor_yPos

	if (kcurs == 0) kgoto ex

		gkValue			=				kcursor_yPos*10
		printk				1, gkValue
		kgoto				nxtmsg
ex:
					endin

					instr			10

aOut				poscil			0.8, gkValue, 1
					outs				aOut, aOut
;					fout				"CsoundTest01.wav", 6, aOut
					endin

</CsInstruments>
<CsScore>
f1 0 32768 10 1

i1  0 65
i10 0 65

e

</CsScore>
</CsoundSynthesizer>
