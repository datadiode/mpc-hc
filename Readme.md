# Media Player Classic - Home Cinema with GPS replay
[![StandWithUkraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/badges/StandWithUkraine.svg)](https://github.com/vshymanskyy/StandWithUkraine/blob/main/docs/README.md)

The motivation for this fork was experiences with a GPS-enabled dash cam which recorded consistently wrong coordinates, and the apparent lack of a player application with the ability to compensate for the error. The error turned out to be reversible through a simple linear coordinate transform. The required correction factors can be obtained by solving a linear equation system with 6 unknowns involving pairs of false and true GPS coordinates from 3 reference locations which describe a sufficiently large triangle within the region where the camera is operated.

My setup to acquire the reference coordinates with help of https://conota.app/:

![wrong-gps-coordinates](https://github.com/user-attachments/assets/35214b91-70b3-448e-a963-905c9cdc643d)

The known pairs of false and true GPS coordinates would be inserted into https://matrixcalc.org/slu.html like so:

![mpc-hc-system-of-equations-2](https://github.com/user-attachments/assets/bc788112-4b05-4818-8ed6-e70f24e06ce4)

The obtained values can then be entered under *Options* &rarr; *Tweaks* so the player can use them during replay.

![mpc-hc-options-tweaks-page](https://github.com/user-attachments/assets/75135d06-70f7-4251-b953-c92be9fa1edd)

Preview with reduced fps showing footage from [https://cycling.vangestel.online/](https://cycling.vangestel.online/indoor/videos/germany/rimberg-kronenberg/) licenced under [CC BY-NC-SA 4.0](http://creativecommons.org/licenses/by-nc-sa/4.0/):

![mpc-hc-with-gps-replay](https://github.com/user-attachments/assets/83b531cd-8ccd-4e66-a1bd-0a2d145cedd3)

# Media Player Classic - Home Cinema

Media Player Classic - Home Cinema (MPC-HC) is a free and open-source video and audio player for Windows. MPC-HC is based on the original Guliverkli project and contains many additional features and bug fixes.

## Development Status

The player is mature, stable, reliable, and already provides a huge amount of features.

Due to a lack of active developers, the player is currently in maintenance mode. This means that there are no direct plans for adding any big new features. Development is currently limited to small bug fixes and updates. However, external developers can still contribute additional fixes and new functionality. In fact, several people have already helped to give the player some new functionality and other improvements.

The internal codecs are developed in an external project ([LAV Filters](https://github.com/Nevcairiel/LAVFilters)). That project is still actively maintained, and MPC-HC will be updated periodically with the latest codecs. Same applies to code/files from other external projects that are used by MPC-HC, such as MediaInfo.

If you are a programmer and want to help improve MPC-HC, then you can do so by submitting a pull request containing your patches.

## Overview of features

A lot of people seem to be unaware of some of the awesome features that have been added to MPC-HC in the past years. Here is a list of useful options and features that everyone should know about:
* Modern GUI Theme (Dark or Light)<br/>
Options > Player > User Interface<br/>
When using modern theme it is also possible to change the height of the seekbar and size of the toolbar buttons.<br/>
* Video preview on the seekbar<br/>
Options > Player > User Interface
* Play HDR video<br/>
This requires using [MPC Video Renderer](https://github.com/clsid2/MPCVideoRenderer/releases) or [madVR](http://forum.doom9.org/showthread.php?t=146228).<br/>
After installation these renderers can be selected here:<br/>
Options > Playback > Output<br/>
Tip: If you want an easy to use all-in-one package that contains MPC-HC and these renderers, then use [K-Lite Codec pack](http://codecguide.com/download_kl.htm).
* Ability to search for subtitles<br/>
Press D for manual search.<br/>
Or enable automatic search in: Options > Subtitles > Misc<br/>
* Adjust playback speed<br/>
Menu > Play > Playback rate<br/>
The buttons in the player that control playback rate take a 2x step by default. This can be customized to smaller values (like 10%):<br/>
Options > Playback > Speed step<br/>
Adjusting playback speed works best with the SaneAR audio renderer. This also has automatic pitch correction.<br/>
Options > Playback > Output > Audio Renderer
* MPC-HC can remember playback position, so you can resume from that point later<br/>
Options > Player > History
* You can quickly seek through a video with Ctrl + Mouse Scrollwheel.
* You can jump to next/previous file in a folder by pressing PageUp/PageDown.
* You can perform automatic actions at end of file. For example to go to next file or close player.<br/>
Options > Playback > After Playback (permanent setting)<br/>
Menu > Play > After Playback (for current file only)
* A-B repeat<br/>
You can loop a segment of a video. Press [ and ] to set start and stop markers.
* You can rotate/flip/mirror/stretch/zoom the video<br/>
Menu > View > Pan&Scan<br/>
This is also easily done with hotkeys (see below).
* There are lots of keyboard hotkeys and mouse actions to control the player. They can be customized as well.<br/>
Options > Player > Keys<br/>
Tip: there is a search box above the table.
* You can stream videos directly from Youtube and many other video websites<br/>
Put [yt-dlp.exe](https://github.com/yt-dlp/yt-dlp/releases) in the MPC-HC installation folder.<br/>
Then you can open website URLs in the player: Menu > File > Open File/URL<br/>
You can even download those videos: Menu > File > Save a copy<br/>
Tip: to be able to download in best quality with yt-dlp, it is recommended to also put [ffmpeg.exe](https://www.gyan.dev/ffmpeg/builds/) in the MPC-HC folder.<br/>
Several YDL configuration options are found here: Options > Advanced<br/>
This includes an option to specify the location of the .exe in case you don't want to put it in MPC-HC folder.<br/>
Note 1: You also need to install [Microsoft Visual C++ 2010 SP1 Redistributable Package (x86)](https://download.microsoft.com/download/1/6/5/165255E7-1014-4D0A-B094-B6A430A6BFFC/vcredist_x86.exe)<br/>
Note 2: [yt-dlp nightly build](https://github.com/yt-dlp/yt-dlp-nightly-builds/) (very latest version made daily)
* Besides all these (new) features, there have also been many bugfixes and internal improvements in the player in the past years that give better performance and stability. It also has updated internal codecs. Support was added for CUE sheets, WebVTT subtitles, etc.

## System Requirements

* Windows 7 / 8 / 8.1 / 10 / 11

## License

MPC-HC's code is licensed under [GPL v3](/COPYING.txt).
