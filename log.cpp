case 0:
	host.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 1:
	connection.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 2:
	cache_control.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 3:
	sec_ch_ua.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 4:
	sec_ch_ua_mobile.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 5:
	sec_ch_ua_platform.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 6:
	upgrade_insecure_requests.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 7:
	user_agent.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 8:
	accept.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 9:
	sec_fetch_site.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 10:
	sec_fetch_mode.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 11:
	sec_fetch_dest.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 12:
	accept_encoding.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break;
case 13:
	accept_language.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
	break
//  case x:
//    referer.assign(tmp_data.begin() + tab[i].size(), tmp_data.end());
//    break;

