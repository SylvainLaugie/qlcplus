/*
  Q Light Controller
  palettegenerator.h

  Copyright (C) Heikki Junnila

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef PALETTEGENERATOR_H
#define PALETTEGENERATOR_H

#include <QString>
#include <QList>
#include <QHash>

#include "qlcchannel.h"

class Fixture;
class Scene;
class Doc;

/**
 * This class can be used on intelligent lights (scanners, moving heads..)
 * to automatically generate functions for their capabilities (color, gobo..)
 * for easy and quick initial setup.
 */
class PaletteGenerator
{
public:
    /**
     * Create a new PaletteGenerator instance.
     *
     * @param doc The Doc object that takes all generated functions
     * @param fxiList List of fixtures to create functions for
     */
    PaletteGenerator(Doc* doc, const QList <Fixture*>& fxiList);

    /** Destructor */
    ~PaletteGenerator();

    /** Create colour macros for each fixture's colour capabilities */
    void createColours();

    /** Create gobo macros for each fixture's gobo capabilities */
    void createGobos();

    /** Create shutter macros for each fixture's shutter capabilities */
    void createShutters();

    /** Find fixture channels that belong to a certain group and have more
        than one capability (i.e. there's something make a palette from) */
    static QList <quint32> findChannels(const Fixture* fixture,
                                        QLCChannel::Group group);

protected:
    /**
     * Create scenes for each capability found from fixture's channels
     * that belong to the given channel group. For example, if $group
     * is "Colour" and $fxi has a colour wheel that has red, green, blue
     * and cyan colours, this generates 4 scenes; one for each colour.
     *
     * All fixtures that contain similar features end up eventually in the
     * same scene so that running a "Cyan" scene will set all fixtures'
     * colour channels to Cyan value.
     *
     * @param fxi The fixture instance to create functions for
     * @param group The channel group to create scenes for
     */
    void createGroupScenes(const Fixture* fxi, QLCChannel::Group group);

    /** Add generated scenes to Doc */
    void addScenesToDoc();

    /** Delete all scenes that haven't been added to Doc */
    void purgeScenes();

private:
    Doc* m_doc;
    QList <Fixture*> m_fixtures;
    QHash <QString,Scene*> m_scenes;
};

#endif

