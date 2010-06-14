/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2010 Arctic Server Team
 * See COPYING for license details.
 */

static uint32 spellarray[CLASS_DRUID+1][9999] = 
{
	{ 0 }, 
	{ 71, 72, 78, 100, 284, 285, 355, 469, 676, 694, 772, 845, 871, 1160, 1161, 1464, 1608, 1680, 1715, 1719, 2048, 2457, 2458, 2565, 2687, 3411, 5242, 5246, 5308, 5530, 6178, 6190, 6192, 6343, 6546, 6547, 6548, 6552, 6572, 6574, 6673, 7369, 7376, 7379, 7381, 7384, 7386, 8198, 8204, 8205, 8820, 11549, 11550, 11551, 11554, 11555, 11556, 11564, 11565, 11566, 11567, 11572, 11573, 11574, 11578, 11580, 11581, 11600, 11601, 11604, 11605, 11608, 11609, 12327, 12678, 12695, 12696, 12705, 12723, 12798, 12886, 12964, 12966, 12967, 12968, 12969, 12970, 12976, 18498, 18499, 19870, 19871, 20230, 20252, 20569, 20647, 20658, 20660, 20661, 20662, 21156, 21551, 21552, 21553, 23880, 23885, 23920, 23922, 23923, 23924, 23925, 25202, 25203, 25208, 25231, 25234, 25236, 25241, 25242, 25248, 25258, 25264, 25269, 25286, 25288, 25289, 26654, 29707, 29841, 29842, 30016, 30022, 30029, 30324, 30330, 30356, 30357, 34428, 45471, 46845, 46856, 46857, 46916, 46946, 46947, 47436, 47437, 47439, 47440, 47449, 47450, 47465, 47470, 47471, 47474, 47475, 47485, 47486, 47487, 47488, 47497, 47498, 47501, 47502, 47519, 47520, 55694, 56112, 57755, 57823, 64380, 64382, }, 
	{ 67, 465, 498, 633, 635, 639, 642, 643, 647, 853, 879, 1022, 1026, 1032, 1038, 1042, 1044, 1152, 2800, 2812, 3472, 4987, 5502, 5588, 5589, 5599, 5614, 5615, 6940, 7294, 7328, 10278, 10290, 10291, 10292, 10293, 10298, 10299, 10300, 10301, 10308, 10310, 10312, 10313, 10314, 10318, 10322, 10324, 10326, 10328, 10329, 19740, 19742, 19746, 19750, 19752, 19834, 19835, 19836, 19837, 19838, 19850, 19852, 19853, 19854, 19876, 19888, 19891, 19895, 19896, 19897, 19898, 19899, 19900, 19939, 19940, 19941, 19942, 19943, 20050, 20052, 20053, 20116, 20154, 20164, 20165, 20166, 20184, 20185, 20186, 20187, 20217, 20249, 20250, 20251, 20271, 20425, 20467, 20772, 20773, 20922, 20923, 20924, 20927, 20928, 20929, 20930, 21084, 24239, 24274, 24275, 25290, 25291, 25292, 25780, 25781, 25782, 25894, 25898, 25899, 25902, 25903, 25911, 25912, 25913, 25914, 25916, 25918, 25997, 26017, 26573, 27135, 27136, 27137, 27138, 27139, 27140, 27141, 27142, 27143, 27149, 27150, 27151, 27152, 27153, 27154, 27173, 27174, 27175, 27176, 27179, 27180, 31789, 31801, 31803, 31804, 31834, 31884, 31898, 32223, 32699, 32700, 32841, 33072, 33073, 33074, 48781, 48782, 48784, 48785, 48788, 48800, 48801, 48805, 48806, 48816, 48817, 48818, 48819, 48820, 48821, 48822, 48823, 48824, 48825, 48826, 48827, 48931, 48932, 48933, 48934, 48935, 48936, 48937, 48938, 48941, 48942, 48943, 48945, 48947, 48949, 48950, 48951, 48952, 53407, 53408, 53489, 53600, 53601, 53651, 53652, 53653, 53654, 53655, 53656, 53657, 53659, 53672, 53726, 53733, 53736, 53742, 54043, 54149, 54152, 54153, 54428, 54968, 59578, 60091, 61411, 62124, 64891, 66922, }, 
	{ 75, 136, 781, 883, 982, 1002, 1130, 1462, 1494, 1495, 1499, 1510, 1513, 1515, 1543, 1978, 2641, 2643, 2973, 2974, 3034, 3043, 3044, 3045, 3111, 3661, 3662, 5116, 5118, 5384, 6197, 6991, 13159, 13161, 13163, 13165, 13481, 13542, 13543, 13544, 13549, 13550, 13551, 13552, 13553, 13554, 13555, 13795, 13797, 13809, 13812, 13813, 14260, 14261, 14262, 14263, 14264, 14265, 14266, 14269, 14270, 14271, 14281, 14282, 14283, 14284, 14285, 14286, 14287, 14288, 14289, 14290, 14294, 14295, 14298, 14299, 14300, 14301, 14302, 14303, 14304, 14305, 14310, 14311, 14314, 14315, 14316, 14317, 14318, 14319, 14320, 14321, 14322, 14323, 14324, 14325, 14326, 14327, 19185, 19263, 19381, 19382, 19383, 19384, 19385, 19579, 19801, 19878, 19879, 19880, 19882, 19883, 19884, 19885, 20043, 20190, 20736, 20900, 20901, 20902, 20903, 20904, 20909, 20910, 24131, 24132, 24133, 24134, 24135, 24395, 24396, 24397, 24406, 24529, 25294, 25295, 25296, 27014, 27016, 27019, 27021, 27022, 27023, 27024, 27025, 27026, 27044, 27045, 27046, 27065, 27067, 27068, 27069, 34026, 34074, 34120, 34471, 34477, 34501, 34600, 34833, 34834, 34835, 34836, 34837, 35098, 35099, 35101, 36916, 42234, 42243, 42244, 42245, 48989, 48990, 48995, 48996, 48998, 48999, 49000, 49001, 49009, 49010, 49011, 49012, 49044, 49045, 49047, 49048, 49049, 49050, 49051, 49052, 49053, 49054, 49055, 49056, 49064, 49065, 49066, 49067, 49071, 53220, 53230, 53254, 53271, 53338, 53339, 53351, 53352, 56453, 56641, 58431, 58432, 58433, 58434, 60051, 60052, 60053, 60192, 60202, 60210, 61005, 61006, 61846, 61847, 62757, 63668, 63669, 63670, 63671, 63672, }, 
	{ 53, 408, 703, 921, 1725, 1752, 1757, 1758, 1759, 1760, 1766, 1776, 1784, 1833, 1842, 1856, 1857, 1860, 1943, 1966, 2070, 2094, 2098, 2589, 2590, 2591, 2836, 2983, 5171, 5277, 5938, 6760, 6761, 6762, 6768, 6770, 6774, 8621, 8623, 8624, 8631, 8632, 8633, 8637, 8639, 8640, 8643, 8647, 8676, 8696, 8721, 8724, 8725, 11267, 11268, 11269, 11273, 11274, 11275, 11279, 11280, 11281, 11289, 11290, 11293, 11294, 11297, 11299, 11300, 11303, 11305, 13977, 14093, 14181, 17347, 17348, 21184, 24224, 25300, 25302, 26669, 26679, 26839, 26861, 26862, 26863, 26864, 26865, 26867, 26884, 26889, 27095, 27096, 27097, 27099, 27441, 27448, 31016, 31125, 31224, 32645, 32684, 34411, 34412, 34413, 48637, 48638, 48656, 48657, 48658, 48659, 48660, 48663, 48666, 48667, 48668, 48671, 48672, 48673, 48674, 48675, 48676, 48689, 48690, 48691, 51637, 51675, 51677, 51680, 51693, 51699, 51722, 51723, 51724, 57933, 57934, 57992, 57993, 58427, 58428,  }, 
	{ 17, 139, 453, 527, 528, 552, 585, 586, 588, 589, 591, 592, 594, 596, 598, 600, 602, 605, 970, 976, 984, 988, 992, 996, 1004, 1006, 1243, 1244, 1245, 1706, 2006, 2010, 2050, 2052, 2053, 2054, 2055, 2060, 2061, 2096, 2767, 2791, 2944, 3747, 6060, 6063, 6064, 6065, 6066, 6074, 6075, 6076, 6077, 6078, 6346, 7001, 7128, 8092, 8102, 8103, 8104, 8105, 8106, 8122, 8124, 8129, 9472, 9473, 9474, 9484, 9485, 10880, 10881, 10888, 10890, 10892, 10893, 10894, 10898, 10899, 10900, 10901, 10909, 10915, 10916, 10917, 10927, 10928, 10929, 10933, 10934, 10937, 10938, 10945, 10946, 10947, 10951, 10952, 10955, 10957, 10958, 10960, 10961, 10963, 10964, 10965, 14743, 14752, 14818, 14819, 14914, 15237, 15261, 15262, 15263, 15264, 15265, 15266, 15267, 15430, 15431, 17311, 17312, 17313, 17314, 18807, 19238, 19240, 19241, 19242, 19243, 19276, 19277, 19278, 19279, 19280, 20770, 21562, 21564, 23455, 23458, 23459, 25210, 25213, 25217, 25218, 25221, 25222, 25233, 25235, 25308, 25312, 25314, 25315, 25316, 25329, 25331, 25363, 25364, 25367, 25368, 25372, 25375, 25384, 25387, 25389, 25392, 25431, 25433, 25435, 25437, 25467, 27681, 27683, 27799, 27800, 27801, 27803, 27804, 27805, 27813, 27817, 27818, 27828, 27841, 27870, 27871, 27873, 27874, 28275, 28276, 32375, 32379, 32546, 32996, 32999, 33076, 33110, 33143, 33151, 33196, 33197, 33198, 33619, 34433, 34754, 34863, 34864, 34865, 34866, 34916, 34917, 34919, 39374, 44416, 45237, 45241, 45242, 47666, 47750, 47757, 47758, 48040, 48045, 48062, 48063, 48065, 48066, 48067, 48068, 48070, 48071, 48072, 48073, 48074, 48075, 48076, 48077, 48078, 48084, 48085, 48086, 48087, 48088, 48089, 48112, 48113, 48119, 48120, 48122, 48123, 48124, 48125, 48126, 48127, 48134, 48135, 48153, 48155, 48156, 48157, 48158, 48159, 48160, 48161, 48162, 48168, 48169, 48170, 48171, 48172, 48173, 48299, 48300, 49821, 49868, 52983, 52984, 52985, 52986, 52987, 52988, 52998, 52999, 53000, 53001, 53002, 53003, 53005, 53006, 53007, 53022, 53023, 56131, 56160, 56161, 63731, 63734, 63735, 64058, 64843, 64844, 64901, 64904, }, 
	{ 3714, 42650, 42651, 43265, 45462, 45463, 45469, 45470, 45477, 45524, 45529, 45902, 46584, 47476, 47528, 47541, 47568, 47632, 47633, 48263, 48265, 48266, 48707, 48721, 48743, 48792, 49020, 49142, 49410, 49560, 49575, 49576, 49892, 49893, 49894, 49895, 49896, 49903, 49904, 49909, 49917, 49918, 49919, 49920, 49921, 49923, 49924, 49926, 49927, 49928, 49929, 49930, 49936, 49937, 49938, 49939, 49940, 49941, 49998, 49999, 50096, 50108, 50109, 50110, 50111, 50444, 50447, 50448, 50449, 50536, 50842, 50977, 51325, 51326, 51327, 51328, 51409, 51410, 51411, 51416, 51417, 51418, 51419, 51423, 51424, 51425, 51969, 51970, 51983, 51986, 52284, 52285, 52286, 52372, 52373, 52374, 52375, 55258, 55259, 55260, 55261, 55262, 55265, 55268, 55270, 55271, 56222, 56815, 56816, 57330, 57532, 57623, 59879, 59921, 61274, 61275, 61276, 61277, 61278, 61455, 61999, 62900, 62901, 62902, 62903, 62904, 66188, 66196, 66198, 66215, 66216, 66217,  }, 
	{ 131, 324, 325, 331, 332, 370, 379, 403, 421, 526, 529, 546, 547, 548, 556, 905, 913, 915, 930, 939, 943, 945, 959, 1064, 1535, 2008, 2062, 2484, 2645, 2825, 2860, 2894, 3599, 3738, 5394, 5675, 5730, 6041, 6196, 6363, 6364, 6365, 6375, 6377, 6390, 6391, 6392, 6495, 8004, 8005, 8008, 8010, 8012, 8017, 8018, 8019, 8024, 8027, 8030, 8033, 8038, 8042, 8044, 8045, 8046, 8050, 8052, 8053, 8056, 8058, 8071, 8075, 8134, 8143, 8154, 8155, 8160, 8161, 8170, 8177, 8181, 8184, 8190, 8227, 8232, 8235, 8249, 8498, 8499, 8512, 10391, 10392, 10395, 10396, 10399, 10406, 10407, 10408, 10412, 10413, 10414, 10427, 10428, 10431, 10432, 10437, 10438, 10442, 10447, 10448, 10456, 10462, 10463, 10466, 10467, 10468, 10472, 10473, 10478, 10479, 10486, 10495, 10496, 10497, 10526, 10537, 10538, 10585, 10586, 10587, 10595, 10600, 10601, 10605, 10622, 10623, 11314, 11315, 15207, 15208, 16177, 16236, 16237, 16253, 16298, 16339, 16341, 16342, 16355, 16356, 16362, 16387, 20608, 20609, 20610, 20776, 20777, 21169, 24398, 25357, 25361, 25391, 25396, 25420, 25422, 25423, 25439, 25442, 25448, 25449, 25454, 25457, 25464, 25469, 25472, 25489, 25500, 25505, 25508, 25509, 25525, 25528, 25533, 25546, 25547, 25552, 25557, 25560, 25563, 25567, 25570, 25574, 25590, 26363, 26364, 26365, 26366, 26367, 26369, 26370, 26371, 26372, 29177, 29178, 29228, 30165, 30669, 30670, 30671, 30708, 30803, 30804, 30805, 30824, 30874, 32175, 32176, 32182, 32593, 32594, 33736, 36591, 36936, 43339, 45284, 45286, 45287, 45288, 45289, 45290, 45291, 45292, 45293, 45294, 45295, 45296, 45297, 45298, 45299, 45300, 45301, 45302, 49230, 49231, 49232, 49233, 49235, 49236, 49237, 49238, 49239, 49240, 49268, 49269, 49270, 49271, 49272, 49273, 49275, 49276, 49277, 49278, 49279, 49280, 49281, 49283, 49284, 51505, 51514, 51730, 51988, 51991, 51992, 51993, 51994, 52127, 52129, 52131, 52134, 52136, 52138, 55166, 55458, 55459, 55533, 57622, 57720, 57721, 57722, 57960, 57994, 58580, 58581, 58582, 58643, 58649, 58652, 58656, 58699, 58703, 58704, 58731, 58734, 58737, 58739, 58741, 58745, 58746, 58749, 58751, 58753, 58755, 58756, 58757, 58771, 58773, 58774, 58785, 58789, 58790, 58794, 58795, 58796, 58801, 58803, 58804, 59156, 59158, 59159, 60043, 60348, 61299, 61300, 61301, 61649, 61657, 63685, 66842, 66843, 66844, }, 
	{ 10, 66, 116, 118, 120, 122, 130, 133, 143, 145, 168, 205, 475, 543, 587, 597, 604, 759, 837, 865, 990, 1008, 1449, 1459, 1460, 1461, 1463, 1953, 2120, 2121, 2136, 2137, 2138, 2139, 2948, 3140, 3552, 3561, 3562, 3563, 3565, 3566, 3567, 5143, 5144, 5145, 5504, 5505, 5506, 6117, 6127, 6129, 6131, 6141, 6143, 7268, 7269, 7270, 7300, 7301, 7302, 7320, 7322, 8400, 8401, 8402, 8406, 8407, 8408, 8412, 8413, 8416, 8417, 8418, 8419, 8422, 8423, 8427, 8437, 8438, 8439, 8444, 8445, 8446, 8450, 8451, 8455, 8457, 8458, 8461, 8462, 8492, 8494, 8495, 10053, 10054, 10059, 10138, 10139, 10140, 10144, 10145, 10148, 10149, 10150, 10151, 10156, 10157, 10159, 10160, 10161, 10169, 10170, 10173, 10174, 10177, 10179, 10180, 10181, 10185, 10186, 10187, 10191, 10192, 10193, 10197, 10199, 10201, 10202, 10205, 10206, 10207, 10211, 10212, 10215, 10216, 10219, 10220, 10223, 10225, 10230, 10273, 10274, 11416, 11417, 11418, 11419, 11420, 12051, 12355, 12484, 12485, 12486, 12494, 12505, 12522, 12523, 12524, 12525, 12526, 12536, 12654, 12824, 12825, 12826, 13018, 13019, 13020, 13021, 13031, 13032, 13033, 18809, 22782, 22783, 22959, 23028, 24530, 25304, 25306, 25345, 25346, 27070, 27071, 27072, 27073, 27074, 27075, 27076, 27078, 27079, 27080, 27082, 27085, 27086, 27087, 27088, 27090, 27101, 27124, 27125, 27126, 27127, 27128, 27130, 27131, 27132, 27133, 27134, 28271, 28272, 28609, 28612, 29077, 29442, 30449, 30451, 30455, 30482, 31643, 32266, 32267, 32271, 32272, 32796, 33041, 33042, 33043, 33405, 33690, 33691, 33717, 33933, 33938, 33944, 33946, 34913, 35715, 35717, 37420, 38692, 38697, 38699, 38700, 38703, 38704, 42198, 42208, 42209, 42210, 42211, 42212, 42213, 42832, 42833, 42841, 42842, 42843, 42844, 42845, 42846, 42858, 42859, 42872, 42873, 42890, 42891, 42894, 42896, 42897, 42913, 42914, 42917, 42920, 42921, 42925, 42926, 42930, 42931, 42937, 42938, 42939, 42940, 42944, 42945, 42949, 42950, 42955, 42956, 42985, 42995, 43002, 43008, 43010, 43012, 43015, 43017, 43019, 43020, 43023, 43024, 43038, 43039, 43043, 43044, 43045, 43046, 43987, 44401, 44413, 44440, 44441, 44450, 44461, 44544, 44614, 44780, 44781, 45438, 47610, 49358, 49359, 49360, 49361, 53140, 53142, 54648, 54741, 54748, 55342, 55359, 55360, 55361, 55362, 58659, 61024, 61025, 61305, 61316, 61721, 61780, 64349, 64350, 70909, 71761, }, 
	{ 126, 132, 172, 348, 603, 686, 687, 688, 689, 691, 693, 695, 696, 697, 698, 699, 702, 705, 706, 707, 709, 710, 712, 755, 980, 1010, 1014, 1086, 1088, 1094, 1098, 1106, 1108, 1120, 1122, 1454, 1455, 1456, 1490, 1714, 1949, 2362, 2941, 3698, 3699, 3700, 5138, 5484, 5500, 5676, 5697, 5699, 5740, 5782, 5857, 6201, 6202, 6205, 6213, 6215, 6217, 6219, 6222, 6223, 6229, 6353, 6366, 6789, 7641, 7646, 7648, 7651, 8288, 8289, 11659, 11660, 11661, 11665, 11667, 11668, 11671, 11672, 11675, 11677, 11678, 11681, 11682, 11683, 11684, 11687, 11688, 11689, 11693, 11694, 11695, 11699, 11700, 11707, 11708, 11711, 11712, 11713, 11719, 11721, 11722, 11725, 11726, 11729, 11730, 11733, 11734, 11735, 11739, 11740, 17727, 17728, 17919, 17920, 17921, 17922, 17923, 17924, 17925, 17926, 17928, 17951, 17952, 17953, 18093, 18540, 18541, 18647, 18662, 18822, 18867, 18868, 18869, 18870, 18871, 18937, 18938, 19483, 20153, 20752, 20755, 20756, 20757, 23759, 23760, 23761, 23762, 23826, 23827, 23828, 23829, 23833, 23834, 23835, 23836, 23837, 23838, 23839, 23840, 23841, 23842, 23843, 23844, 25307, 25309, 25311, 27209, 27210, 27211, 27212, 27213, 27214, 27215, 27216, 27217, 27218, 27219, 27220, 27222, 27223, 27224, 27228, 27230, 27238, 27243, 27250, 27259, 27260, 27263, 27265, 27285, 28172, 28176, 28189, 28610, 29722, 29858, 29886, 29893, 30404, 30405, 30413, 30414, 30459, 30545, 30546, 30909, 30910, 31117, 32231, 32386, 32388, 32389, 32390, 32391, 34936, 35702, 35703, 35704, 35705, 35706, 42218, 42223, 42224, 42225, 42226, 47206, 47241, 47261, 47262, 47263, 47264, 47265, 47793, 47808, 47809, 47810, 47811, 47812, 47813, 47814, 47815, 47817, 47818, 47819, 47820, 47822, 47823, 47824, 47825, 47826, 47827, 47833, 47834, 47835, 47836, 47837, 47838, 47841, 47843, 47846, 47847, 47855, 47856, 47857, 47859, 47860, 47863, 47864, 47865, 47867, 47871, 47878, 47884, 47886, 47888, 47889, 47890, 47891, 47892, 47893, 47897, 48018, 48020, 50511, 50581, 50589, 53756, 54352, 54785, 54817, 54879, 57946, 58284, 58887, 58889, 59092, 59161, 59163, 59164, 59170, 59171, 59172, 59671, 59673, 60219, 60220, 61191, 61290, 61610,  }, 
	{ 99, 339, 467, 740, 768, 769, 770, 774, 779, 780, 782, 783, 1058, 1062, 1066, 1075, 1079, 1082, 1126, 1178, 1430, 1735, 1822, 1823, 1824, 1850, 2090, 2091, 2637, 2782, 2893, 2908, 2912, 3025, 3029, 3137, 3627, 5176, 5177, 5178, 5179, 5180, 5185, 5186, 5187, 5188, 5189, 5195, 5196, 5201, 5209, 5211, 5215, 5217, 5221, 5225, 5229, 5232, 5234, 5420, 5421, 5487, 6756, 6778, 6780, 6785, 6787, 6793, 6795, 6798, 6800, 6807, 6808, 6809, 8903, 8905, 8907, 8910, 8914, 8918, 8921, 8924, 8925, 8926, 8927, 8928, 8929, 8936, 8938, 8939, 8940, 8941, 8946, 8949, 8950, 8951, 8955, 8972, 8983, 8992, 8998, 9000, 9005, 9007, 9490, 9492, 9493, 9634, 9635, 9745, 9747, 9750, 9752, 9754, 9756, 9758, 9821, 9823, 9824, 9826, 9827, 9829, 9830, 9833, 9834, 9835, 9839, 9840, 9841, 9845, 9846, 9849, 9850, 9852, 9853, 9856, 9857, 9858, 9862, 9863, 9866, 9867, 9875, 9876, 9880, 9881, 9884, 9885, 9888, 9889, 9892, 9894, 9896, 9898, 9901, 9904, 9908, 9910, 9912, 16689, 16810, 16811, 16812, 16813, 16857, 16914, 16952, 16954, 16958, 16961, 16979, 17329, 17401, 17402, 18657, 18658, 18960, 20484, 20719, 20739, 20742, 20747, 20748, 21178, 21849, 21850, 22568, 22570, 22812, 22827, 22828, 22829, 22842, 22845, 24248, 24905, 24907, 24974, 24975, 24976, 24977, 25297, 25298, 25299, 26978, 26979, 26980, 26981, 26982, 26983, 26984, 26985, 26986, 26987, 26988, 26989, 26990, 26991, 26992, 26994, 26995, 26996, 26997, 26998, 27000, 27001, 27002, 27003, 27004, 27005, 27006, 27007, 27008, 27009, 27012, 27013, 29166, 31018, 31709, 33357, 33745, 33763, 33786, 33876, 33878, 33891, 33943, 33982, 33983, 33986, 33987, 34299, 40120, 42230, 42231, 42232, 42233, 44203, 44205, 44206, 44207, 44208, 48377, 48378, 48435, 48436, 48437, 48440, 48441, 48442, 48443, 48444, 48445, 48446, 48447, 48450, 48451, 48459, 48461, 48462, 48463, 48464, 48465, 48466, 48467, 48468, 48469, 48470, 48477, 48479, 48480, 48559, 48560, 48561, 48562, 48563, 48564, 48565, 48566, 48567, 48568, 48569, 48570, 48571, 48572, 48573, 48574, 48575, 48576, 48577, 48578, 48579, 49376, 49799, 49800, 49802, 49803, 49804, 50212, 50213, 50322, 50464, 50763, 50764, 50765, 50766, 50767, 50768, 50769, 52610, 53199, 53200, 53201, 53223, 53225, 53226, 53227, 53248, 53249, 53251, 53307, 53308, 53312, 54755, 61384, 61387, 61388, 61390, 61391, 62078, 62600, 64801, 66530, }, 
};
