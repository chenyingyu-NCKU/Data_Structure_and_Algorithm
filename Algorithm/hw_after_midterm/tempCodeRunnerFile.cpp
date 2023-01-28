map<int, list<int> >::iterator it;
        list<int>::iterator i;
        for(it = parent.begin(); it != parent.end(); it++){
            for(i = (*it).second.begin(); i != (*it).second.end(); i++){
                if((*i) == out){
                    (*it).second.erase(i); // remove the parent
                    break;
                }
            }
            if((*it).second.size() == 0){ // ready to be print
                que.insert((*it).first);
                parent.erase(it);
            }
        }