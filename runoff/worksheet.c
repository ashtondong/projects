  for (int i = 0; i < voter_count; i++)
    {   // second loop sets the candidate preference rank
        for (int j = 0; j < candidate_count; j++)
        {   // third loop finds the candidate name in the candidate array
            for (int k = 0; k < candidate_count; k++)

            {
                if (strcmp (candidates[k].name, name) == 0)
                {//if found, set the voter and preference number to the name
                    preferences[i][j] = k;
                    return true;
                }

            }
        }

    }