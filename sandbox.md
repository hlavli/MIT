
<script type="text/javascript" id="MathJax-script" async
  src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js">https://github.com/TomasChovanec/MIT/blob/main/sandbox.md
</script>

$$ \Large Ftimer = CPU Frequency / Prescalar $$

$$\Large Ftimer = 16MHz/1024 = 15.625KHz $$

$$ \Large Ttick = 1/ 15.625K = 64 \mu seconds$$

$$Ttotal = 64\mu s X 255 = 16ms$$


$$Ftimer = CPU Frequency/Prescalar $$ $$Ftimer = 16MHz/1024 = 15.625KHz $$

$$Ttick = 1/ 15.625K = 64 \mu seconds$$ $$Ttotal = 64\mu s X 65536 = 4 seconds$$

So that is 4 secs! We just need 100 msec so, $$100ms/64\mu s = 1562 = 0x061A$$

$$ \Large Ftimer = CPU Frequency / Prescalar $$

$$
\Large t_{\text{tick}} = \frac{Frequency}{Prescaler} = \frac{16e6}{64} \, \mu\text{s}
$$

$$
\Large t_{\text{tick}} = \frac{64}{16 \times 10^6} = 4 \, \mu\text{s}
$$

$$
\Large t_{\text{tick}} = \frac{N_{\text{prescaler}}}{f_{\text{clk}}}
$$
