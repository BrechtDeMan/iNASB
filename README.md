# iNtelligent Audio Switch Box

_**WIP: this project was developed in November 2014, and has yet to be updated to the current version of [JUCE](https://www.juce.com)**_

## Authors

[Brecht De Man](https://github.com/BrechtDeMan), Tom (Artyom) Arjannikov, [Nikolay Glazyrin](https://github.com/nglazyrin/), [Simon-Claudius Wystrach](http://github.com/thebaronhimself)

iNASB is actually a clever acronym of the creators' initials: **N**ikolay, **A**rtyom, **S**imon and **B**recht! 

## Background

iNASB is the result of a last-minute idea and a random meetup of four people at the the HAMR2014 hackathon, organised by Lab Rosa at Columbia. It took place during the weekend of 25-26 October at Academia Sinica’s Institute of Information Science in Taipei, Taiwan, immediately before the 15th ISMIR conference there and consisting entirely of conference delegates. See http://labrosa.ee.columbia.edu/hamr_ismir2014/ for more information. 

Original page: http://labrosa.ee.columbia.edu/hamr_ismir2014/proceedings/doku.php?id=intelligent_audio_switch_box

Original repository: https://bitbucket.org/bogonetic/inasbv1


## Instructions

iNASB is a VST or Audio Unit plugin that routes an audio signal to one channel or another, based on the characteristics of the signal. It automatically learns what channel to switch to during a training stage, when the audio to be associated with the given channel is recorded. The plugin is ready to use after both channels have some audio associated with them.

An example usage is the augmentation of an instrument performance by providing control over any kind of audio effect by parameters embedded in the performance itself, such as pitch, level, or timbral features. E.g. a guitarist who desires harmonic distortion only on the higher notes, a vocalist who wants a long echo on the really loud hits, or a trombone that needs a flanger on slides between notes. It can also be used in less creative, more functional ways to control level, dynamics or spectrum. 

![Plugin screenshot](/docs/images/iNASBplugin.png)

### Parameters

- **GAIN** Amplification level of the input signal.

- **THRESHOLD** The value of discrimination between channel A and B.

- **HYSTERESIS** A noise gate that perpetuates the current state. 

- **INERTIA** Determines how fast to apply parameter changes, for example, a high inertia setting will create a sweeping effect.


### Learning

During the learning stage, four spectral features (centroid, flatness, crest and roll-off) are extracted from training examples. They are associated with one of the channels and stored in memory. The user would toggle "Train A" or "Train B" button and then produce sound for the plugin to learn from. The "Finish" button completes the training stage, and the plugin becomes ready to route the signal.

During the playback mode an algorithm finds the training example(s) nearest to the features extracted real-time from sound and the corresponding class routes the sound signal to the appropriate channel.


## Dependencies

iNASB is a VST plugin or Audio Unit created with [JUCE](https://www.juce.com) and the [VST SDK](http://www.steinberg.net/sdk_downloads/vstsdk365_12_11_2015_build_67.zip). 


## Awards

For this hack, our team received the prize for 'Best Code' - one of three HAMR trophies. The trophy is a hammer (get it?). 

![Plugin screenshot](/docs/images/trophy.jpg)
