import json
import os

with open('package_loranodes_index.json', 'r') as file:
    data = json.load(file)

toInsert = {}

# user input version number
toInsert['version'] = input('file version? ')

toInsert['boards'] = []
toInsert['boards'].append({'name': 'microNode'})

toInsert['archiveFileName'] = 'microNode-' + toInsert['version'] + '.tar.bz2'

toInsert['checksum'] = 'SHA-256:' + input('sha256 sum? ')

toInsert['url'] = 'https://github.com/loranodes/arduino-core/' \
    + toInsert['version'] + '/' + toInsert['archiveFileName']

cmd = toInsert['archiveFileName']
toInsert['size'] = os.path.getsize(cmd)


toInsert['architecture'] = 'samd'
toInsert['name'] = 'LoRaNodes M0 Boards'
toInsert['category'] = 'LoRaNodes'

toInsert['help'] = {'online': 'https://github.com/loranodes'}

toInsert['toolsDependencies'] = []

tool1 = {"name": "arm-none-eabi-gcc", "packager": "arduino", "version": "4.8.3-2014q1"}
tool2 = {"name": "bossac", "packager": "arduino", "version": "1.6.1-arduino"}
tool3 = {"name": "openocd", "packager": "arduino", "version": "0.9.0-arduino"}
tool4 = {"name": "CMSIS", "packager": "arduino", "version": "4.0.0-atmel"}

toInsert['toolsDependencies'].append(tool1)
toInsert['toolsDependencies'].append(tool2)
toInsert['toolsDependencies'].append(tool3)
toInsert['toolsDependencies'].append(tool4)


data['packages'][0]['platforms'].append(toInsert)

with open('package_loranodes_index.json', 'w') as file:
    json.dump(data, file, indent="\t")

print('\n\nNow commit this and tag the release with the tag "' + toInsert['version'] + '"')
