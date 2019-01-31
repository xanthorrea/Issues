
-- Remove Old pack58 Table
DROP TABLE IF EXISTS `pack58`;

-- Create New boost_pack Table
CREATE TABLE `boost_pack`
(
  `class` smallint(5) UNSIGNED NOT NULL,
  `type` smallint(5) UNSIGNED NOT NULL,
  `item` mediumint(8) UNSIGNED NOT NULL COMMENT 'item id',
  `count` mediumint(8) NOT NULL DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Pack 58
INSERT INTO `boost_pack` (`class`, `type`, `item`, `count`) VALUES
(1, 0, 11815, 1), -- Hand of Justice
(1, 0, 11933, 1), -- Imperial Jewel
(1, 0, 12653, 1), -- Riphook
(1, 0, 13098, 1), -- Painweaver Band
(1, 0, 13361, 2), -- Skullforge Reaver
(1, 0, 13373, 1), -- Band of Flesh
(1, 0, 16730, 1), -- Breastplate of Valor
(1, 0, 16731, 1), -- Helm of Valor
(1, 0, 16732, 1), -- Legplates of Valor
(1, 0, 16733, 1), -- Spaulders of Valor
(1, 0, 16734, 1), -- Boots of Valor
(1, 0, 16735, 1), -- Bracers of Valor
(1, 0, 16736, 1), -- Belt of Valor
(1, 0, 16737, 1), -- Gauntlets of Valor
(1, 0, 22321, 1), -- Heart of Wyrmthalak
(1, 0, 22337, 1), -- Shroud of Domination
(1, 2, 11669, 1), -- Naglering
(1, 2, 11810, 1), -- Force of Will
(1, 2, 12602, 1), -- Draconian Deflector
(1, 2, 12929, 1), -- Emberfury Talisman
(1, 2, 12940, 1), -- Dal'Rend's Sacred Charge
(1, 2, 12952, 1), -- Gyth's Skull
(1, 2, 13380, 1), -- Willey's Portable Howitzer
(1, 2, 13955, 1), -- Stoneform Shoulders
(1, 2, 18383, 1), -- Force Imbued Gauntlets
(1, 2, 18466, 1), -- Royal Seal of Eldre'Thalas
(1, 2, 18503, 1), -- Kromcrush's Chestplate
(1, 2, 18521, 1), -- Grimy Metal Boots
(1, 2, 18689, 1), -- Phantasmal Cloak
(1, 2, 18690, 1), -- Wraithplate Leggings
(1, 2, 18754, 1), -- Fel Hardened Bracers
(1, 2, 19051, 1), -- Girdle of the Dawn
(1, 2, 22331, 1), -- Band of the Steadfast Hero
(2, 0, 11815, 1), -- Hand of Justice
(2, 0, 11933, 1), -- Imperial Jewel
(2, 0, 12583, 1), -- Blackhand Doomsaw
(2, 0, 13098, 1), -- Painweaver Band
(2, 0, 13203, 1), -- Armswake Cloak
(2, 0, 13373, 1), -- Band of Flesh
(2, 0, 16730, 1), -- Breastplate of Valor
(2, 0, 16731, 1), -- Helm of Valor
(2, 0, 16732, 1), -- Legplates of Valor
(2, 0, 16733, 1), -- Spaulders of Valor
(2, 0, 16734, 1), -- Boots of Valor
(2, 0, 16735, 1), -- Bracers of Valor
(2, 0, 16736, 1), -- Belt of Valor
(2, 0, 16737, 1), -- Gauntlets of Valor
(2, 0, 22321, 1), -- Heart of Wyrmthalak
(2, 0, 22401, 1), -- Libram of Hope
(2, 1, 11819, 1), -- Second Wind
(2, 1, 11923, 1), -- The Hammer of Grace
(2, 1, 13178, 1), -- Rosewine Circle
(2, 1, 16722, 1), -- Lightforge Bracers
(2, 1, 16723, 1), -- Lightforge Belt
(2, 1, 16724, 1), -- Lightforge Gauntlets
(2, 1, 16725, 1), -- Lightforge Boots
(2, 1, 16726, 1), -- Lightforge Breastplate
(2, 1, 16727, 1), -- Lightforge Helm
(2, 1, 16728, 1), -- Lightforge Legplates
(2, 1, 16729, 1), -- Lightforge Spaulders
(2, 1, 18472, 1), -- Royal Seal of Eldre'Thalas
(2, 1, 19530, 1), -- Caretaker's Cape
(2, 1, 22327, 1), -- Amulet of the Redeemed
(2, 1, 22334, 1), -- Band of Mending
(2, 1, 22336, 1), -- Draconian Aegis of the Legion
(2, 1, 23201, 1), -- Libram of Divinity
(2, 2, 11669, 1), -- Naglering
(2, 2, 11810, 1), -- Force of Will
(2, 2, 13091, 1), -- Medallion of Grand Marshal Morris
(2, 2, 14620, 1), -- Deathbone Girdle
(2, 2, 14621, 1), -- Deathbone Sabatons
(2, 2, 14622, 1), -- Deathbone Gauntlets
(2, 2, 14623, 1), -- Deathbone Legguards
(2, 2, 14624, 1), -- Deathbone Chestplate
(2, 2, 18048, 1), -- Mastersmith's Hammer
(2, 2, 18384, 1), -- Bile-etched Spaulders
(2, 2, 18472, 1), -- Royal Seal of Eldre'Thalas
(2, 2, 18689, 1), -- Phantasmal Cloak
(2, 2, 18718, 1), -- Grand Crusader's Helm
(2, 2, 18754, 1), -- Fel Hardened Bracers
(2, 2, 21753, 1), -- Gem Studded Band
(2, 2, 22336, 1), -- Draconian Aegis of the Legion
(2, 2, 22400, 1), -- Libram of Truth
(3, 0, 11933, 1), -- Imperial Jewel
(3, 0, 13098, 1), -- Painweaver Band
(3, 0, 13340, 1), -- Cape of the Black Baron
(3, 0, 16674, 1), -- Beaststalker's Tunic
(3, 0, 16675, 1), -- Beaststalker's Boots
(3, 0, 16676, 1), -- Beaststalker's Gloves
(3, 0, 16677, 1), -- Beaststalker's Cap
(3, 0, 16678, 1), -- Beaststalker's Pants
(3, 0, 16679, 1), -- Beaststalker's Mantle
(3, 0, 16680, 1), -- Beaststalker's Belt
(3, 0, 16681, 1), -- Beaststalker's Bindings
(3, 0, 18473, 1), -- Royal Seal of Eldre'Thalas
(3, 0, 18680, 1), -- Ancient Bone Bow
(3, 0, 18701, 1), -- Innervating Band
(3, 0, 19991, 1), -- Devilsaur Eye
(3, 0, 22314, 1), -- Huntsman's Harpoon
(4, 0, 11815, 1), -- Hand of Justice
(4, 0, 13340, 1), -- Cape of the Black Baron
(4, 0, 13361, 1), -- Skullforge Reaver
(4, 0, 13953, 1), -- Silent Fang
(4, 0, 16707, 1), -- Shadowcraft Cap
(4, 0, 16708, 1), -- Shadowcraft Spaulders
(4, 0, 16709, 1), -- Shadowcraft Pants
(4, 0, 16710, 1), -- Shadowcraft Bracers
(4, 0, 16711, 1), -- Shadowcraft Boots
(4, 0, 16712, 1), -- Shadowcraft Gloves
(4, 0, 16713, 1), -- Shadowcraft Belt
(4, 0, 16721, 1), -- Shadowcraft Tunic
(4, 0, 18500, 1), -- Tarnished Elven Ring
(4, 0, 18701, 1), -- Innervating Band
(4, 0, 22321, 1), -- Heart of Wyrmthalak
(4, 0, 22340, 1), -- Pendant of Celerity
(4, 0, 28972, 1), -- Flightblade Throwing Axe
(5, 1, 11819, 1), -- Second Wind
(5, 1, 13392, 1), -- The Postmaster's Seal
(5, 1, 16690, 1), -- Devout Robe
(5, 1, 16691, 1), -- Devout Sandals
(5, 1, 16692, 1), -- Devout Gloves
(5, 1, 16693, 1), -- Devout Crown
(5, 1, 16694, 1), -- Devout Skirt
(5, 1, 16695, 1), -- Devout Mantle
(5, 1, 16696, 1), -- Devout Belt
(5, 1, 16697, 1), -- Devout Bracers
(5, 1, 18469, 1), -- Royal Seal of Eldre'Thalas
(5, 1, 19530, 1), -- Caretaker's Cape
(5, 1, 22254, 1), -- Wand of Eternal Light
(5, 1, 22327, 1), -- Amulet of the Redeemed
(5, 1, 22334, 1), -- Band of Mending
(5, 1, 22394, 1), -- Staff of Metanoia
(5, 3, 0, 1),
(5, 3, 11832, 1), -- Burst of Knowledge
(5, 3, 12926, 1), -- Flaming Band
(5, 3, 12930, 1), -- Briarwood Reed
(5, 3, 12968, 1), -- Frostweaver Cape
(5, 3, 13396, 1), -- Skul's Ghastly Touch
(5, 3, 16682, 1), -- Magister's Boots
(5, 3, 16683, 1), -- Magister's Bindings
(5, 3, 16684, 1), -- Magister's Gloves
(5, 3, 16685, 1), -- Magister's Belt
(5, 3, 16686, 1), -- Magister's Crown
(5, 3, 16687, 1), -- Magister's Leggings
(5, 3, 16688, 1), -- Magister's Robes
(5, 3, 16689, 1), -- Magister's Mantle
(5, 3, 18691, 1), -- Dark Advisor's Pendant
(5, 3, 22335, 1), -- Lord Valthalak's Staff of Command
(5, 3, 22339, 1), -- Rune Band of Wizardry
(7, 0, 11815, 1), -- Hand of Justice
(7, 0, 11933, 1), -- Imperial Jewel
(7, 0, 12621, 2), -- Demonfork
(7, 0, 13098, 1), -- Painweaver Band
(7, 0, 13203, 1), -- Armswake Cloak
(7, 0, 13373, 1), -- Band of Flesh
(7, 0, 16674, 1), -- Beaststalker's Tunic
(7, 0, 16675, 1), -- Beaststalker's Boots
(7, 0, 16676, 1), -- Beaststalker's Gloves
(7, 0, 16677, 1), -- Beaststalker's Cap
(7, 0, 16678, 1), -- Beaststalker's Pants
(7, 0, 16679, 1), -- Beaststalker's Mantle
(7, 0, 16680, 1), -- Beaststalker's Belt
(7, 0, 16681, 1), -- Beaststalker's Bindings
(7, 0, 22321, 1), -- Heart of Wyrmthalak
(7, 0, 22395, 1), -- Totem of Rage
(7, 1, 11819, 1), -- Second Wind
(7, 1, 11923, 1), -- The Hammer of Grace
(7, 1, 13178, 1), -- Rosewine Circle
(7, 1, 16666, 1), -- Vest of Elements
(7, 1, 16667, 1), -- Coif of Elements
(7, 1, 16668, 1), -- Kilt of Elements
(7, 1, 16669, 1), -- Pauldrons of Elements
(7, 1, 16670, 1), -- Boots of Elements
(7, 1, 16671, 1), -- Bindings of Elements
(7, 1, 16672, 1), -- Gauntlets of Elements
(7, 1, 16673, 1), -- Cord of Elements
(7, 1, 19530, 1), -- Caretaker's Cape
(7, 1, 22268, 1), -- Draconic Infused Emblem
(7, 1, 22327, 1), -- Amulet of the Redeemed
(7, 1, 22334, 1), -- Band of Mending
(7, 1, 22336, 1), -- Draconian Aegis of the Legion
(7, 1, 22345, 1), -- Totem of Rebirth
(7, 3, 10829, 1), -- Dragon's Eye
(7, 3, 12926, 1), -- Flaming Band
(7, 3, 12930, 1), -- Briarwood Reed
(7, 3, 12967, 1), -- Bloodmoon Cloak
(7, 3, 13964, 1), -- Witchblade
(7, 3, 16666, 1), -- Vest of Elements
(7, 3, 16667, 1), -- Coif of Elements
(7, 3, 16668, 1), -- Kilt of Elements
(7, 3, 16669, 1), -- Pauldrons of Elements
(7, 3, 16670, 1), -- Boots of Elements
(7, 3, 16671, 1), -- Bindings of Elements
(7, 3, 16672, 1), -- Gauntlets of Elements
(7, 3, 16673, 1), -- Cord of Elements
(7, 3, 18471, 1), -- Royal Seal of Eldre'Thalas
(7, 3, 22336, 1), -- Draconian Aegis of the Legion
(7, 3, 22395, 1), -- Totem of Rage
(7, 3, 22433, 1), -- Don Mauricio's Band of Domination
(8, 3, 10829, 1), -- Dragon's Eye
(8, 3, 11832, 1), -- Burst of Knowledge
(8, 3, 12926, 1), -- Flaming Band
(8, 3, 12930, 1), -- Briarwood Reed
(8, 3, 12967, 1), -- Bloodmoon Cloak
(8, 3, 13938, 1), -- Bonecreeper Stylus
(8, 3, 16682, 1), -- Magister's Boots
(8, 3, 16683, 1), -- Magister's Bindings
(8, 3, 16684, 1), -- Magister's Gloves
(8, 3, 16685, 1), -- Magister's Belt
(8, 3, 16686, 1), -- Magister's Crown
(8, 3, 16687, 1), -- Magister's Leggings
(8, 3, 16688, 1), -- Magister's Robes
(8, 3, 16689, 1), -- Magister's Mantle
(8, 3, 22335, 1), -- Lord Valthalak's Staff of Command
(8, 3, 22433, 1), -- Don Mauricio's Band of Domination
(9, 3, 10829, 1), -- Dragon's Eye
(9, 3, 11832, 1), -- Burst of Knowledge
(9, 3, 12926, 1), -- Flaming Band
(9, 3, 12967, 1), -- Bloodmoon Cloak
(9, 3, 13938, 1), -- Bonecreeper Stylus
(9, 3, 16698, 1), -- Dreadmist Mask
(9, 3, 16699, 1), -- Dreadmist Leggings
(9, 3, 16700, 1), -- Dreadmist Robe
(9, 3, 16701, 1), -- Dreadmist Mantle
(9, 3, 16702, 1), -- Dreadmist Belt
(9, 3, 16703, 1), -- Dreadmist Bracers
(9, 3, 16704, 1), -- Dreadmist Sandals
(9, 3, 16705, 1), -- Dreadmist Wraps
(9, 3, 18467, 1), -- Royal Seal of Eldre'Thalas
(9, 3, 22335, 1), -- Lord Valthalak's Staff of Command
(9, 3, 22433, 1), -- Don Mauricio's Band of Domination
(11, 0, 11815, 1), -- Hand of Justice
(11, 0, 13047, 1), -- Twig of the World Tree
(11, 0, 13340, 1), -- Cape of the Black Baron
(11, 0, 16707, 1), -- Shadowcraft Cap
(11, 0, 16708, 1), -- Shadowcraft Spaulders
(11, 0, 16709, 1), -- Shadowcraft Pants
(11, 0, 16710, 1), -- Shadowcraft Bracers
(11, 0, 16711, 1), -- Shadowcraft Boots
(11, 0, 16712, 1), -- Shadowcraft Gloves
(11, 0, 16713, 1), -- Shadowcraft Belt
(11, 0, 16721, 1), -- Shadowcraft Tunic
(11, 0, 18500, 1), -- Tarnished Elven Ring
(11, 0, 18701, 1), -- Innervating Band
(11, 0, 22321, 1), -- Heart of Wyrmthalak
(11, 0, 22340, 1), -- Pendant of Celerity
(11, 0, 22397, 1), -- Idol of Ferocity
(11, 1, 11819, 1), -- Second Wind
(11, 1, 13392, 1), -- The Postmaster's Seal
(11, 1, 16706, 1), -- Wildheart Vest
(11, 1, 16714, 1), -- Wildheart Bracers
(11, 1, 16715, 1), -- Wildheart Boots
(11, 1, 16716, 1), -- Wildheart Belt
(11, 1, 16717, 1), -- Wildheart Gloves
(11, 1, 16718, 1), -- Wildheart Spaulders
(11, 1, 16719, 1), -- Wildheart Kilt
(11, 1, 16720, 1), -- Wildheart Cowl
(11, 1, 18470, 1), -- Royal Seal of Eldre'Thalas
(11, 1, 19530, 1), -- Caretaker's Cape
(11, 1, 22327, 1), -- Amulet of the Redeemed
(11, 1, 22334, 1), -- Band of Mending
(11, 1, 22394, 1), -- Staff of Metanoia
(11, 1, 22398, 1), -- Idol of Rejuvenation
(11, 3, 11832, 1), -- Burst of Knowledge
(11, 3, 12926, 1), -- Flaming Band
(11, 3, 12930, 1), -- Briarwood Reed
(11, 3, 12967, 1), -- Bloodmoon Cloak
(11, 3, 16706, 1), -- Wildheart Vest
(11, 3, 16714, 1), -- Wildheart Bracers
(11, 3, 16715, 1), -- Wildheart Boots
(11, 3, 16716, 1), -- Wildheart Belt
(11, 3, 16717, 1), -- Wildheart Gloves
(11, 3, 16718, 1), -- Wildheart Spaulders
(11, 3, 16719, 1), -- Wildheart Kilt
(11, 3, 16720, 1), -- Wildheart Cowl
(11, 3, 18289, 1), -- Barbed Thorn Necklace
(11, 3, 22335, 1), -- Lord Valthalak's Staff of Command
(11, 3, 22433, 1); -- Don Mauricio's Band of Domination

-- Pack 70
INSERT INTO `boost_pack` (`class`, `type`, `item`, `count`) VALUES
(1, 4, 28403, 1), -- Doomplate Chestguard
(1, 4, 27497, 1), -- Doomplate Gauntlets
(1, 4, 28225, 1), -- Doomplate Warhelm
(1, 4, 27870, 1), -- Doomplate Legguards
(1, 4, 27771, 2), -- Doomplate Shoulderguards
(1, 4, 27551, 1), -- Skeletal Necklace of Battlerage
(1, 4, 27892, 1), -- Cloak of the Inciter
(1, 4, 34789, 1), -- Bracers of Slaughter
(1, 4, 27985, 1), -- Deathforge Girdle
(1, 4, 28318, 1), -- Obsidian Clodstompers
(1, 4, 27904, 1), -- Resounding Ring of Glory
(1, 4, 27460, 1), -- Reavers' Ring
(1, 4, 28034, 1), -- Hourglass of the Unraveller
(1, 4, 28288, 1), -- Abacus of Violent Odds
(1, 4, 28367, 1), -- Greatsword of Forlorn Visions
(1, 4, 27794, 1), -- Recoilless Rocket Ripper X-54
(1, 4, 34703, 1), -- Latro's Dancing Blade
(1, 4, 28189, 1), -- Latro's Shifting Sword
(1, 4, 28316, 1), -- Aegis of the Sunbird
(1, 6, 28205, 1), -- Breastplate of the Bold
(1, 6, 27475, 1), -- Gauntlets of the Bold
(1, 6, 27977, 1), -- Legplates of the Bold
(1, 6, 27803, 1), -- Shoulderguards of the Bold
(1, 6, 28350, 1), -- Warhelm of the Bold
(1, 6, 27792, 1), -- Steam-Hinge Chain of Valor
(1, 6, 27804, 1), -- Devilshark Cape
(1, 6, 27459, 1), -- Vambraces of Daring
(1, 6, 27672, 1), -- Girdle of the Immovable
(1, 6, 27813, 1), -- Boots of the Colossus
(1, 6, 27822, 1), -- Crystal Band of Valor
(1, 6, 27740, 1), -- Band of Ursol
(1, 6, 27891, 1), -- Adamantine Figurine
(1, 6, 27529, 1), -- Figurine of the Colossus
(1, 6, 27476, 1), -- Truncheon of Five Hells
(1, 6, 28316, 1), -- Aegis of the Sunbird
(1, 6, 32780, 1), -- The Boomstick
(2, 4, 28203, 1), -- Breastplate of the Righteous
(2, 4, 27535, 1), -- Gauntlets of the Righteous
(2, 4, 28285, 1), -- Helm of the Righteous
(2, 4, 27839, 1), -- Legplates of the Righteous
(2, 4, 27739, 1), -- Spaulders of the Righteous
(2, 4, 27792, 1), -- Steam-Hinge Chain of Valor
(2, 4, 27988, 1), -- Burnoose of Shifting Ages
(2, 4, 27459, 1), -- Vambraces of Daring
(2, 4, 27672, 1), -- Girdle of the Immovable
(2, 4, 32778, 1), -- Boots of Righteous Fortitude
(2, 4, 27822, 1), -- Crystal Band of Valor
(2, 4, 27805, 1), -- Ring of the Silver Hand
(2, 4, 28223, 1), -- Arcanist's Stone
(2, 4, 27529, 1), -- Figurine of the Colossus
(2, 4, 27937, 1), -- Sky Breaker
(2, 4, 28316, 1), -- Aegis of the Sunbird
(2, 4, 27917, 1), -- Libram of the Eternal Rest
(2, 5, 27897, 1), -- Breastplate of Many Graces
(2, 5, 27790, 1), -- Mask of Penance
(2, 5, 27748, 1), -- Cassock of the Loyal
(2, 5, 27539, 1), -- Justice Bearer's Pauldrons
(2, 5, 27457, 1), -- Life Bearer's Gauntlets
(2, 5, 28233, 1), -- Necklace of Resplendent Hope
(2, 5, 27448, 1), -- Cloak of the Everliving
(2, 5, 27489, 1), -- Virtue Bearer's Vambraces
(2, 5, 27548, 1), -- Girdle of Many Blessings
(2, 5, 28221, 1), -- Boots of the Watchful Heart
(2, 5, 28259, 1), -- Cosmic Lifeband
(2, 5, 27491, 1), -- Signet of Repose
(2, 5, 27828, 1), -- Warp-Scarab Brooch
(2, 5, 28223, 1), -- Arcanist's Stone
(2, 5, 27538, 1), -- Lightsworn Hammer
(2, 5, 31292, 1), -- Crystal Pulse Shield
(2, 5, 28296, 1), -- Libram of the Lightbringer
(2, 6, 28403, 1), -- Doomplate Chestguard
(2, 6, 27497, 1), -- Doomplate Gauntlets
(2, 6, 28225, 1), -- Doomplate Warhelm
(2, 6, 27870, 1), -- Doomplate Legguards
(2, 6, 27771, 1), -- Doomplate Shoulderguards
(2, 6, 27551, 1), -- Skeletal Necklace of Battlerage
(2, 6, 27892, 1), -- Cloak of the Inciter
(2, 6, 34789, 1), -- Bracers of Slaughter
(2, 6, 27985, 1), -- Deathforge Girdle
(2, 6, 27884, 1), -- Ornate Boots of the Sanctified
(2, 6, 27904, 1), -- Resounding Ring of Glory
(2, 6, 27460, 1), -- Reavers' Ring
(2, 6, 28034, 1), -- Hourglass of the Unraveller
(2, 6, 28288, 1), -- Abacus of Violent Odds
(2, 6, 28393, 1), -- Warmaul of Infused Light
(2, 6, 27484, 1), -- Libram of Avengement
(3, 4, 28228, 1), -- Beast Lord Cuirass
(3, 4, 27474, 1), -- Beast Lord Handguards
(3, 4, 28275, 1), -- Beast Lord Helm
(3, 4, 27874, 1), -- Beast Lord Leggings
(3, 4, 27801, 1), -- Beast Lord Mantle
(3, 4, 27546, 1), -- Traitor's Noose
(3, 4, 27878, 1), -- Auchenai Death Shroud
(3, 4, 34698, 1), -- Bracers of the Forest Stalker
(3, 4, 27541, 1), -- Archery Belt of the Broken
(3, 4, 27915, 1), -- Sky-Hunter Swift Boots
(3, 4, 27925, 1), -- Ravenclaw Band
(3, 4, 27453, 1), -- Averinn's Ring of Slaying
(3, 4, 28034, 1), -- Hourglass of the Unraveller
(3, 4, 28121, 1), -- Icon of Unyielding Courage
(3, 4, 28263, 1), -- Stellaris
(3, 4, 28397, 1), -- Emberhawk Crossbow
(3, 4, 30611, 1), -- Halaani Razorshaft
(4, 4, 28264, 1), -- Wastewalker Tunic
(4, 4, 27531, 1), -- Wastewalker Gloves
(4, 4, 28224, 1), -- Wastewalker Helm
(4, 4, 27837, 1), -- Wastewalker Leggings
(4, 4, 27797, 1), -- Wastewalker Shoulderpads
(4, 4, 27546, 1), -- Traitor's Noose
(4, 4, 27878, 1), -- Auchenai Death Shroud
(4, 4, 27712, 1), -- Shackles of Quagmirran
(4, 4, 27911, 1), -- Epoch's Whispering Cinch
(4, 4, 27867, 1), -- Boots of the Unjust
(4, 4, 27925, 1), -- Ravenclaw Band
(4, 4, 27453, 1), -- Averinn's Ring of Slaying
(4, 4, 28034, 1), -- Hourglass of the Unraveller
(4, 4, 28121, 1), -- Icon of Unyielding Courage
(4, 4, 34703, 1), -- Latro's Dancing Blade
(4, 4, 28189, 1), -- Latro's Shifting Sword
(4, 4, 34783, 1), -- Nightstrike
(5, 5, 28413, 1), -- Hallowed Crown
(5, 5, 28230, 1), -- Hallowed Garments
(5, 5, 27536, 1), -- Hallowed Handwraps
(5, 5, 27775, 1), -- Hallowed Pauldrons
(5, 5, 27875, 1), -- Hallowed Trousers
(5, 5, 28233, 1), -- Necklace of Resplendent Hope
(5, 5, 27448, 1), -- Cloak of the Everliving
(5, 5, 27452, 1), -- Light Scribe Bands
(5, 5, 27542, 1), -- Cord of Belief
(5, 5, 27919, 1), -- Light-Woven Slippers
(5, 5, 27491, 1), -- Signet of Repose
(5, 5, 27996, 1), -- Ring of Spiritual Precision
(5, 5, 28370, 1), -- Bangle of Endless Blessings
(5, 5, 27828, 1), -- Warp-Scarab Brooch
(5, 5, 28216, 1), -- Dathrohan's Ceremonial Hammer
(5, 5, 28213, 1), -- Lordaeron Medical Guide
(5, 7, 28193, 1), -- Mana-Etched Crown
(5, 7, 27465, 1), -- Mana-Etched Gloves
(5, 7, 27907, 1), -- Mana-Etched Pantaloons
(5, 7, 28191, 1), -- Mana-Etched Vestments
(5, 7, 27796, 1), -- Mana-Etched Spaulders
(5, 7, 28134, 1), -- Brooch of Heightened Potential
(5, 7, 34792, 1), -- Cloak of the Betrayed
(5, 7, 27462, 1), -- Crimson Bracers of Gloom
(5, 7, 27795, 1), -- Sash of Serpentra
(5, 7, 27451, 1), -- Boots of the Darkwalker
(5, 7, 27784, 1), -- Scintillating Coral Band
(5, 7, 28227, 1), -- Sparking Arcanite Ring
(5, 7, 28223, 1), -- Arcanist's Stone
(5, 7, 27683, 1), -- Quagmirran's Eye
(5, 7, 27937, 1), -- Sky Breaker
(5, 7, 28187, 1), -- Star-Heart Lamp
(7, 4, 28231, 1), -- Tidefury Chestpiece
(7, 4, 27510, 1), -- Tidefury Gauntlets
(7, 4, 28349, 2), -- Tidefury Helm
(7, 4, 27909, 1), -- Tidefury Kilt
(7, 4, 27802, 1), -- Tidefury Shoulderguards
(7, 4, 28134, 1), -- Brooch of Heightened Potential
(7, 4, 28269, 1), -- Baba's Cloak of Arcanistry
(7, 4, 27522, 1), -- World's End Bracers
(7, 4, 27743, 1), -- Girdle of Living Flame
(7, 4, 27845, 1), -- Magma Plume Boots
(7, 4, 32779, 1), -- Band of Frigid Elements
(7, 4, 28227, 1), -- Sparking Arcanite Ring
(7, 4, 28223, 1), -- Arcanist's Stone
(7, 4, 28418, 1), -- Shiffar's Nexus-Horn
(7, 4, 27741, 1), -- Bleeding Hollow Warhammer
(7, 4, 27910, 1), -- Silvermoon Crest Shield
(7, 4, 28248, 1), -- Totem of the Void
(7, 5, 27936, 1), -- Greaves of Desolation
(7, 5, 28401, 1), -- Hauberk of Desolation
(7, 5, 27528, 1), -- Gauntlets of Desolation
(7, 5, 28192, 1), -- Helm of Desolation
(7, 5, 27713, 1), -- Pauldrons of Desolation
(7, 5, 27495, 1), -- Soldier's Dog Tags
(7, 5, 27878, 1), -- Auchenai Death Shroud
(7, 5, 34698, 1), -- Bracers of the Forest Stalker
(7, 5, 27541, 1), -- Archery Belt of the Broken
(7, 5, 28384, 1), -- Outland Striders
(7, 5, 27740, 1), -- Band of Ursol
(7, 5, 27904, 1), -- Resounding Ring of Glory
(7, 5, 28034, 1), -- Hourglass of the Unraveller
(7, 5, 28288, 1), -- Abacus of Violent Odds
(7, 5, 27846, 1), -- Claw of the Watcher
(7, 5, 28210, 1), -- Bloodskull Destroyer
(7, 5, 27815, 1), -- Totem of the Astral Winds
(7, 7, 27826, 1), -- Mantle of the Sea Wolf
(7, 7, 27806, 1), -- Fathomheart Gauntlets
(7, 7, 27912, 1), -- Harness of the Deep Currents
(7, 7, 27458, 1), -- Oceansong Kilt
(7, 7, 27759, 1), -- Headdress of the Tides
(7, 7, 28233, 1), -- Necklace of Resplendent Hope
(7, 7, 27448, 1), -- Cloak of the Everliving
(7, 7, 28194, 1), -- Primal Surge Bracers
(7, 7, 27835, 1), -- Stillwater Girdle
(7, 7, 27549, 1), -- Wavefury Boots
(7, 7, 28259, 1), -- Cosmic Lifeband
(7, 7, 27491, 1), -- Signet of Repose
(7, 7, 27828, 1), -- Warp-Scarab Brooch
(7, 7, 28223, 1), -- Arcanist's Stone
(7, 7, 27538, 1), -- Lightsworn Hammer
(7, 7, 27714, 1), -- Swamplight Lantern
(7, 7, 27544, 1), -- Totem of Spontaneous Regrowth
(8, 7, 28278, 1), -- Incanter's Cowl
(8, 7, 27508, 1), -- Incanter's Gloves
(8, 7, 27738, 1), -- Incanter's Pauldrons
(8, 7, 28229, 1), -- Incanter's Robe
(8, 7, 27838, 1), -- Incanter's Trousers
(8, 7, 28134, 1), -- Brooch of Heightened Potential
(8, 7, 34792, 1), -- Cloak of the Betrayed
(8, 7, 27462, 1), -- Crimson Bracers of Gloom
(8, 7, 27795, 1), -- Sash of Serpentra
(8, 7, 27902, 1), -- Silent Slippers of Meditation
(8, 7, 27784, 1), -- Scintillating Coral Band
(8, 7, 28227, 1), -- Sparking Arcanite Ring
(8, 7, 28223, 1), -- Arcanist's Stone
(8, 7, 28418, 1), -- Shiffar's Nexus-Horn
(8, 7, 27905, 1), -- Greatsword of Horrid Dreams
(8, 7, 28187, 1), -- Star-Heart Lamp
(9, 7, 27537, 1), -- Gloves of Oblivion
(9, 7, 28415, 1), -- Hood of Oblivion
(9, 7, 28232, 1), -- Robe of Oblivion
(9, 7, 27778, 1), -- Spaulders of Oblivion
(9, 7, 27948, 1), -- Trousers of Oblivion
(9, 7, 28134, 1), -- Brooch of Heightened Potential
(9, 7, 34792, 1), -- Cloak of the Betrayed
(9, 7, 27462, 1), -- Crimson Bracers of Gloom
(9, 7, 27795, 1), -- Sash of Serpentra
(9, 7, 27902, 1), -- Silent Slippers of Meditation
(9, 7, 27784, 1), -- Scintillating Coral Band
(9, 7, 28227, 1), -- Sparking Arcanite Ring
(9, 7, 28223, 1), -- Arcanist's Stone
(9, 7, 27683, 1), -- Quagmirran's Eye
(9, 7, 27543, 1), -- Starlight Dagger
(9, 7, 28187, 1), -- Star-Heart Lamp
(11, 4, 28348, 1), -- Moonglade Cowl
(11, 4, 28268, 1), -- Natural Mender's Wraps
(11, 4, 34796, 1), -- Robes of Summer Flame
(11, 4, 27800, 1), -- Earthsoul Britches
(11, 4, 27737, 1), -- Moonglade Shoulders
(11, 4, 28233, 1), -- Necklace of Resplendent Hope
(11, 4, 27448, 1), -- Cloak of the Everliving
(11, 4, 27827, 1), -- Lucid Dream Bracers
(11, 4, 28398, 1), -- The Sleeper's Cord
(11, 4, 28251, 1), -- Boots of the Glade-Keeper
(11, 4, 27996, 1), -- Ring of Spiritual Precision
(11, 4, 27491, 1), -- Signet of Repose
(11, 4, 28370, 1), -- Bangle of Endless Blessings
(11, 4, 27828, 1), -- Warp-Scarab Brooch
(11, 4, 27791, 1), -- Serpentcrest Life-Staff
(11, 4, 27886, 1), -- Idol of the Emerald Queen
(11, 5, 27763, 1), -- Crown of the Forest Lord
(11, 5, 27818, 1), -- Starry Robes of the Crescent
(11, 5, 27492, 1), -- Moonchild Leggings
(11, 5, 28255, 1), -- Lunar-Claw Pauldrons
(11, 5, 28214, 1), -- Grips of the Lunar Eclipse
(11, 5, 28134, 1), -- Brooch of Heightened Potential
(11, 5, 28269, 1), -- Baba's Cloak of Arcanistry
(11, 5, 27483, 1), -- Moon-Touched Bands
(11, 5, 27783, 1), -- Moonrage Girdle
(11, 5, 27914, 1), -- Moonstrider Boots
(11, 5, 27784, 1), -- Scintillating Coral Band
(11, 5, 32779, 1), -- Band of Frigid Elements
(11, 5, 28223, 1), -- Arcanist's Stone
(11, 5, 28418, 1), -- Shiffar's Nexus-Horn
(11, 5, 27842, 1), -- Grand Scepter of the Nexus-Kings
(11, 5, 27518, 1), -- Ivory Idol of the Moongoddess
(11, 7, 28264, 1), -- Wastewalker Tunic
(11, 7, 27531, 1), -- Wastewalker Gloves
(11, 7, 28224, 1), -- Wastewalker Helm
(11, 7, 27837, 1), -- Wastewalker Leggings
(11, 7, 27797, 1), -- Wastewalker Shoulderpads
(11, 7, 30710, 1), -- Blood Guard's Necklace of Ferocity
(11, 7, 27892, 1), -- Cloak of the Inciter
(11, 7, 27712, 1), -- Shackles of Quagmirran
(11, 7, 32769, 1), -- Belt of the Raven Lord
(11, 7, 27467, 1), -- Silent-Strider Kneeboots
(11, 7, 27740, 1), -- Band of Ursol
(11, 7, 27925, 1), -- Ravenclaw Band
(11, 7, 28034, 1), -- Hourglass of the Unraveller
(11, 7, 28288, 1), -- Abacus of Violent Odds
(11, 7, 28372, 1), -- Idol of Feral Shadows
(11, 7, 27877, 1); -- Draenic Wildstaff

ALTER TABLE `boost_pack` ADD PRIMARY KEY (`class`,`type`,`item`);
