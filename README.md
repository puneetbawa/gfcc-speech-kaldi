# gfcc-speech-kaldi

**If you use this code or part of it, please cite us!**

The success of any ASR system is dependent on the availability of its training data. However, output in low resource-speaking language is deteriorated due to the absence of sufficient signals processing features. In case of Indian tonal languages like Punjabi, one such difficulty is nearly zero resource conditions and language differences exist due to speaking and vocal tract length differences between children and audlt speech data. 

The code attempts to create the Punjabi Children ASR structure with mismatched settings, with rigorous sound methods such as the Mel frequency cepstral factor (MFCC) and more noise robust methods employing gammatone frequency cepstral factor (GFCC).

1) Puneet Bawa , Virender Kadyan, "Noise robust in-domain children speech enhancement for automatic Punjabi recognition system under mismatched conditions" 
   doi: https://doi.org/10.1016/j.apacoust.2020.107810 

|Datasets		                                       |                                             DNN%			                                     |		
                                                      |		MFCC		                                |	              GFCC		                   |
|Training Set	                        |Testing Set   |	MFCC  |	MFCC + PITCH | MFCC + Pitch + VTLN |	GFCC	|GFCC + PITCH |	GFCC + Pitch + VTLN|
|Female_Adult + Child + Random Noise	|Clean Child	|18.19%	|17.87%	       |17.43%	              |12.36%	|12.01%	     |11.35%                |
	                                    |Noisy Child	|17.93%	|17.36%	       |17.02%	              |12.09%	|11.77%	     |10.91%                |


