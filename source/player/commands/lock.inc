CMD:lock(playerid, params[])
{
    extract params -> new lock; else
    {
        SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /lock [1 - 2]");
        return SCM(playerid, blue, "[Подсказка]: {FFFFFF}1 - личный транспорт | 2 - рабочий транспорт");
    }
    switch(lock)
    {
        case 1:
        {
            if(player_ownable_car[playerid] == -1) return SCM(playerid, red, "У вас нет личного транспорта, или он не заспавнен.");
            
            new Float:car_x, Float: car_y, Float:car_z;
            GetVehiclePos(player_ownable_car[playerid], car_x, car_y, car_z);
            if(!IsPlayerInRangeOfPoint(playerid, 5.0, car_x, car_y, car_z)) return SCM(playerid, red, "Вы должны находится возле своего транспорта.");

            vehicle[player_ownable_car[playerid]][veh_lock] = (vehicle[player_ownable_car[playerid]][veh_lock] == true) ? (false) : (true);

            new engine, lights, alarm, doors, bonnet, boot, objective;
            GetVehicleParamsEx(player_ownable_car[playerid], engine, lights, alarm, doors, bonnet, boot, objective);	
            SetVehicleParamsEx(player_ownable_car[playerid], engine, lights, alarm, vehicle[player_ownable_car[playerid]][veh_lock], bonnet, boot, objective);

            SaveOwnableCar(playerid);

            if(vehicle[player_ownable_car[playerid]][veh_lock] == true)
            {
                GameTextForPlayer(playerid, "~r~LOCK", 2000, 3);
                PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
            }
            else
            {
                GameTextForPlayer(playerid, "~g~LOCK", 2000, 3);
                PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
            }
        }
        case 2:
        {

            if(player_job_vehicle_arend[playerid] != -1)
            {
                new vehicleid = player_job_vehicle_arend[playerid];
                new Float: pos[3];
                GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
                if(!IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2])) return SCM(playerid, red, "Вы должны находится возле транспорта.");

                vehicle[vehicleid][veh_lock] = (vehicle[vehicleid][veh_lock] == true) ? (false) : (true);

                new engine, lights, alarm, doors, bonnet, boot, objective;
                GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);	
                SetVehicleParamsEx(vehicleid, engine, lights, alarm, vehicle[vehicleid][veh_lock], bonnet, boot, objective);

                if(vehicle[vehicleid][veh_lock] == true)
                {
                    GameTextForPlayer(playerid, "~r~LOCK", 2000, 3);
                    PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
                }
                else
                {
                    GameTextForPlayer(playerid, "~g~LOCK", 2000, 3);
                    PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
                }                
            }
            if(player_job_vehicle_created[playerid] != -1)
            {
                new vehicleid = player_job_vehicle_created[playerid];
                new Float: pos[3];      
                GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
                if(!IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2])) return SCM(playerid, red, "Вы должны находится возле транспорта.");

                vehicle[vehicleid][veh_lock] = (vehicle[vehicleid][veh_lock] == true) ? (false) : (true);

                new engine, lights, alarm, doors, bonnet, boot, objective;
                GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);	
                SetVehicleParamsEx(vehicleid, engine, lights, alarm, vehicle[vehicleid][veh_lock], bonnet, boot, objective);

                if(vehicle[vehicleid][veh_lock] == true)
                {
                    GameTextForPlayer(playerid, "~r~LOCK", 2000, 3);
                    PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
                }
                else
                {
                    GameTextForPlayer(playerid, "~g~LOCK", 2000, 3);
                    PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
                }           
            }
            else
            {
                SCM(playerid, red, "Вы не арендуете транспорт.");
            }

        }
        default: 
        {
            SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /lock [1 - 2]");
            return SCM(playerid, blue, "[Подсказка]: {FFFFFF}1 - личный транспорт | 2 - рабочий транспорт");
        }
    }
    return 1;
}