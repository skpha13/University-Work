answer = """
        Exercise 07:

    Psemnal = 90dB => 
        Psemnal = 10 * log10(Psignal_normal)
        90 = 10 * log10(Psignal_normal)
        9 = log10(Psignal_normal)
        Psignal_normal = 10^9
    
    SNRdB = 10 * log10(Psignal_normal / Pnoise_normal)
    80 = 10 * log10(10^9 / Pnoise_normal)
    8 = log10(10^9 / Pnoise_normal)
    10^8 = 10^9 / Pnoise_normal
    Pnoise_normal = 10^9 / 10^8 = 10
    
    Where:
        - Psignal_normal and Pnoise_normal represent the actual power values, not in logarithmic scale (dB).
"""

print(answer)
