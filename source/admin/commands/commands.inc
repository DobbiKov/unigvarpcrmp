new Command1LVL[14][] =
{
    {"{"cblue"}/admins {ffffff}- Администраторы онлайн\n"},
    {"{"cblue"}/weap {ffffff}- Оружие игрока\n"},
    {"{"cblue"}/stats {ffffff}- Посмотреть статистику игрока\n"},
    {"{"cblue"}/freeze {ffffff}- Заморозить игрока\n"},
    {"{"cblue"}/unfreeze {ffffff}- Разморозить игрока\n"},
    {"{"cblue"}/ans {ffffff}- Ответить игроку\n"},
    {"{"cblue"}/youtubers {ffffff}- Список ютуберов\n"},
    {"{"cblue"}/y {ffffff}- Связь ютуберов и администраторов\n"},
    {"{"cblue"}/yhelp {ffffff}- Команды ютуберов\n"},
    {"{"cblue"}/a {ffffff}- Админский чат\n"},
    {"{"cblue"}/ahelp {ffffff}- Команды администраторов\n"},
    {"{"cblue"}/spawnplayer {ffffff}- Заспавнить игрока\n"},
    {"{"cblue"}/sp {ffffff}- Слежка за игроком\n"},
    {"{"cblue"}/spoff {ffffff}- Прекратить слежку за игроком\n"}
};

new Command2LVL[26][] = 
{
    {"{"cblue"}/tp {ffffff}- Телепорт\n"},
    {"{"cblue"}/goto {ffffff}- Телепорт к игроку\n"},
    {"{"cblue"}/gethere {ffffff}- Телепортировать игрока к себе\n"},
    {"{"cblue"}/skick {ffffff}- Тихий кик\n"},
    {"{"cblue"}/kick {ffffff}- Кикнуть игрока\n"},
    {"{"cblue"}/getcar {ffffff}- Телепортировать авто к себе\n"},
    {"{"cblue"}/gotocar {ffffff}- Телепортироваться к авто\n"},
    {"{"cblue"}/msg {ffffff}- Общий чат\n"},
    {"{"cblue"}/gruz {ffffff}- Доставить груз к игроку\n"},
    {"{"cblue"}/jail {ffffff}- Посадить игрока в деморган\n"},
    {"{"cblue"}/mute {ffffff}- Выдать мут игроку\n"},
    {"{"cblue"}/hp {ffffff}- Установить себе здоровье в количестве 100 единиц.\n"},
    {"{"cblue"}/arm {ffffff}- Установить себе броню к количестве 100 единиц\n"},
    {"{"cblue"}/getskin {ffffff}- Взять себе временный скин\n"},
    {"{"cblue"}/resetgun {ffffff}- Забрать оружие у игрока\n"},
    {"\n"},
    {"{"cblue"}Быстрые наказания:\n"},
    {"{"cblue"}/mg {ffffff}- Выдать мут за MG\n"},
    {"{"cblue"}/dm {ffffff}- Посадить игрока в деморган за ДМ\n"},
    {"{"cblue"}/nonrp {ffffff}- Посадить игрока в деморган за NonRP\n"},
    {"{"cblue"}/epp {ffffff}- Посадить игрока в деморган за ЕПП\n"},
    {"{"cblue"}/drive {ffffff}- Посадить игрока в деморган за NonRP езду\n"},
    {"{"cblue"}/caps {ffffff}- Выдать мут за CapsLock\n"},
    {"{"cblue"}/flood {ffffff}- Выдать мут за Flood\n"},
    {"{"cblue"}/offtop {ffffff}- Выдать мут за Offtop\n"},
    {"{"cblue"}/bh {ffffff}- Наказать за BH(Бани Хоп)\n"}
};

new Command3LVL[31][] = 
{
    {"{"cblue"}/setvw {ffffff}- Установить игроку виртуальный мир\n"},
    {"{"cblue"}/setint {ffffff}- Установить игроку интерьер\n"},
    {"{"cblue"}/getip{ffffff}- Узнать IP-Address игрока\n"},
    {"{"cblue"}/offgetip {ffffff}- Узнать IP-Address игрока в оффлайне\n"},
    {"{"cblue"}/cc {ffffff}- Очистить чат\n"},
    {"{"cblue"}/unjail {ffffff}- Выпустить игрока из деморгана\n"},
    {"{"cblue"}/unmute {ffffff}- Снять мут с игрока\n"},
    {"{"cblue"}/fixveh {ffffff}- Починить авто\n"},
    {"{"cblue"}/setfuel {ffffff}- Установить бензин в автомобиле\n"},
    {"{"cblue"}/respawncar {ffffff}- Заспавнить авто по ID\n"},
    {"{"cblue"}/respawncars {ffffff}- Заспавнить авто в радиусе\n"},
    {"{"cblue"}/sethp {ffffff}- Установаить игроку уровень здоровья\n"},
    {"{"cblue"}/setarm {ffffff}- Установить игроку уровень брони\n"},
    {"{"cblue"}/setskin {ffffff}- Установить временный скин игроку\n"},
    {"{"cblue"}/givegun {ffffff}- Выдать оружие игроку\n"},
    {"{"cblue"}/fly {ffffff}- Режим полета\n"},
    {"{"cblue"}/offget {ffffff}- Статистика игрока в оффлайне\n"},
    {"{"cblue"}/ban {ffffff}- Заблокировать аккаунт игроку (онлайн/оффлайн)\n"},
    {"{"cblue"}/warn {ffffff}- выдать предупреждение на аккаунт игрока(онлайн/оффлайн)\n"},
    {"\n"},
    {"{"cblue"}Команды мероприятий:\n"},
    {"{"cblue"}/mpstart {ffffff}- Создать мероприятие\n"},
    {"{"cblue"}/mpstop {ffffff}- Завершить мероприятие\n"},
    {"{"cblue"}/mp {ffffff}- Открыть/закрыть телепорт на мероприятие\n"},
    {"{"cblue"}/mphp {ffffff}- Выдать здоровье участникам мероприятия\n"},
    {"{"cblue"}/mpskin {ffffff}- Выдать скин участникам мероприятия\n"},
    {"{"cblue"}/mpgun {ffffff}- Выдать оружие участникам мероприятия\n"},
    {"{"cblue"}/mphere {ffffff}- Телепортировать к себе участников мероприятия\n"},
    {"{"cblue"}/mpfreeze {ffffff}- Заморозить участников мероприятия\n"},
    {"{"cblue"}/mpunfreeze {ffffff}- Разморозить участников мероприятия\n"},
    {"{"cblue"}/mpsay {ffffff}- Сказать что-то участникам мероприятия\n"}
};

new Command4LVL[9][] = 
{
    {"{"cblue"}/veh {ffffff}- Созать автомобиль\n"},
    {"{"cblue"}/delveh {ffffff}- Удалить автомобиль\n"},
    {"{"cblue"}/alldelveh {ffffff}- Удалить весь транспорт созданный администраторами\n"},
    {"{"cblue"}/offmute {ffffff}- Выдать игроку блокировку чата в оффлайне\n"},
    {"{"cblue"}/offjail {ffffff}- Посадить игрока в деморган в оффлайне\n"},
    {"{"cblue"}/jetpack {ffffff}- Выдать себе JetPack\n"},
    {"{"cblue"}/tpcoord {ffffff}- Телепорт по координатам\n"},
    {"{"cblue"}/fstats {ffffff}- Статистика работ/организаций\n"},
    {"{"cblue"}/auninvite {ffffff}- Уволить игрока из организации\n"}
};

new Command5LVL[5][] = 
{
    {"{"cblue"}/settime {ffffff}- Установить время на сервере\n"},
    {"{"cblue"}/setweather {ffffff}- Установить погоду на сервере\n"},
    {"{"cblue"}/templeader {ffffff}- Выдать временную лидерку\n"},
    {"{"cblue"}/createradar {ffffff}- Создать радар\n"},
    {"{"cblue"}/serverpanel {ffffff}- Панель настройки сервера\n"}
};

new Command6LVL[13][] = 
{
    {"{"cblue"}/setplayerskin {ffffff}- установить игроку постоянный скин\n"},
    {"{"cblue"}/givemoney {ffffff}- Выдать игроку денег\n"},
    {"{"cblue"}/setyoutube {ffffff}- Установить уровень Ютуберки\n"},
    {"{"cblue"}/setleader {ffffff}- Поставить игрока на пост лидера\n"},
    {"{"cblue"}/agl {ffffff}- Выдать игроку лицензии\n"},
    {"{"cblue"}/lwarn {ffffff}- Выдать выговор лидеру организации\n"},
    {"{"cblue"}/unlwarn {ffffff}- Снять выговор лидеру организации\n"},
    {"{"cblue"}/offlwarn {ffffff}- Выдать выговор лидеру в оффлайне\n"},
    {"{"cblue"}/awarn {ffffff}- Выдать выговор администратору\n"},
    {"{"cblue"}/offawarn {ffffff}- Выдать выговор администратору в оффлайне\n"},
    {"{"cblue"}/unawarn {ffffff}- Снять выговор администратору\n"},
    {"{"cblue"}/agivevoen {ffffff}- выдать военный билет игроку\n"},
    {"{"cblue"}/crashplayer {ffffff}- Крашнуть игрока\n"}
};

new Command7LVL[15][] = 
{
    {"{"cblue"}/restart {ffffff}- Перезагрузить сервер\n"},
    {"{"cblue"}/x2day {ffffff}- Включить X2 день\n"},
    {"{"cblue"}/setstat {ffffff}- Редактировать статистику игрока\n"},
    {"{"cblue"}/loadfs {ffffff}- Загрузить скрипт\n"},
    {"{"cblue"}/unloadfs {ffffff}- Отключить скрипт\n"},
    {"{"cblue"}/resetmoney {ffffff}- Обнулить деньги игроку\n"},
    {"{"cblue"}/setadmin {ffffff}- Поставить игрока на пост администратора\n"},
    {"{"cblue"}/aup {ffffff}- Повысить уровень администратора\n"},
    {"{"cblue"}/adown {ffffff}- Понизить уровень администора\n"},
    {"{"cblue"}/addbusiness {ffffff}- Создать бизнес\n"},
    {"{"cblue"}/addhouse {ffffff}- Создать дом\n"},
    {"{"cblue"}/sethousecarpos {ffffff}- Установить дому место спавна авто\n"},
    {"{"cblue"}/addpod {ffffff}- Создать подъезд\n"},
    {"{"cblue"}/setpodcarpos {ffffff}- Установить подъезду место спавна авто\n"},
    {"{"cblue"}/addtoilet {ffffff}- Создать туалет\n"}
};