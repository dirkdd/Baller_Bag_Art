#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "./library/my_ffmpeg_conversion.hpp"
#include "./library/metadata_function.hpp"
#include "./library/dna_generator.hpp"
#include "./library/utils.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc>=2){
        srand(time(NULL));
        const int scale = 1024;
        const string outputFormat = "gif";
        const bool randomized = true;
        const bool unique = true;
        const bool shuffleOutput = true;
        vector<int> collectionSize = {100,100,350,350,350,750,750,750,750,750};
        const vector<vector<string>> layerDir = 
        {
    {"SKILL_Type", "BACKGROUND_RARE", "BULLDOG_Shoes", "BULLDOG_Pants", "BULLDOG_Arms", "BULLDOG_Shirt", "BULLDOG_Necklace", "BULLDOG_Move", "BULLDOG_Ball", "BULLDOG_Glasses", "SKILL_Agility_Rare", "SKILL_Defense_Rare", "SKILL_Explosiveness_Rare", "SKILL_Handling_Rare", "SKILL_XP_Rare"},
    {"SKILL_Type", "BACKGROUND_RARE", "SHAM_GOD_Shoes", "SHAM_GOD_Pants", "SHAM_GOD_Arms", "SHAM_GOD_Shirt", "SHAM_GOD_Necklace", "SHAM_GOD_Move", "SHAM_GOD_Ball", "SHAM_GOD_Glasses", "SKILL_Agility_Rare", "SKILL_Defense_Rare", "SKILL_Explosiveness_Rare", "SKILL_Handling_Rare", "SKILL_XP_Rare"},
    {"SKILL_Type", "BACKGROUND", "BETWEEN_BEHIND_THE_BACK_Shoes", "BETWEEN_BEHIND_THE_BACK_Pants", "BETWEEN_BEHIND_THE_BACK_Arms", "BETWEEN_BEHIND_THE_BACK_Shirt", "BETWEEN_BEHIND_THE_BACK_Move", "BETWEEN_BEHIND_THE_BACK_Ball", "BETWEEN_BEHIND_THE_BACK_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"},
    {"SKILL_Type", "BACKGROUND", "BETWEEN_CROSSOVER_Shoes", "BETWEEN_CROSSOVER_Pants", "BETWEEN_CROSSOVER_Arms", "BETWEEN_CROSSOVER_Shirt", "BETWEEN_CROSSOVER_Move", "BETWEEN_CROSSOVER_Ball", "BETWEEN_CROSSOVER_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"},
    {"SKILL_Type", "BACKGROUND", "SPIN_CYCLE_MOVE_Shoes", "SPIN_CYCLE_MOVE_Pants", "SPIN_CYCLE_MOVE_Arms", "SPIN_CYCLE_MOVE_Shirt", "SPIN_CYCLE_MOVE_Move", "SPIN_CYCLE_MOVE_Ball", "SPIN_CYCLE_MOVE_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"},
    {"SKILL_Type", "BACKGROUND", "IN_N_OUT_Shoes", "IN_N_OUT_Pants", "IN_N_OUT_Arms", "IN_N_OUT_Shirt", "IN_N_OUT_Move", "IN_N_OUT_Ball", "IN_N_OUT_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"},
    {"SKILL_Type", "BACKGROUND", "HESITATION_Shoes", "HESITATION_Pants", "HESITATION_Arms", "HESITATION_Shirt", "HESITATION_Move", "HESITATION_Ball", "HESITATION_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"},
    {"SKILL_Type", "BACKGROUND", "CROSSOVER_Shoes", "CROSSOVER_Pants", "CROSSOVER_Arms", "CROSSOVER_Shirt", "CROSSOVER_Move", "CROSSOVER_Ball", "CROSSOVER_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"},
    {"SKILL_Type", "BACKGROUND", "BETWEEN_THE_LEGS_Shoes", "BETWEEN_THE_LEGS_Pants", "BETWEEN_THE_LEGS_Arms", "BETWEEN_THE_LEGS_Shirt", "BETWEEN_THE_LEGS_Move", "BETWEEN_THE_LEGS_Ball", "BETWEEN_THE_LEGS_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"},
    {"SKILL_Type", "BACKGROUND", "BEHIND_THE_BACK_Shoes", "BEHIND_THE_BACK_Pants", "BEHIND_THE_BACK_Arms", "BEHIND_THE_BACK_Shirt", "BEHIND_THE_BACK_Move", "BEHIND_THE_BACK_Ball", "BEHIND_THE_BACK_Glasses", "SKILL_Agility", "SKILL_Defense", "SKILL_Explosiveness", "SKILL_Handling", "SKILL_XP"}
    
        };
        
        const string name = "Baller Bag Handles Package";
        const string description = "5,000 of the most unique, animated basketball moves in the world.";
        const string baseUri = "https://ballerbag.io";
        const vector<pair<string,string>> extraMetadata = 
        {
        {"Creator", "Justin Ho"}    
        };
        
        //only if u select Solana Chain
        const string symbol = "BallerBag";
        const string family = "BallerBag";
        const string sellerFeeBasisPoints = "750";
        const string externalUrl = "ballerbag.io";
        const vector<string> address = {"3XoRfWGPCoovn7wnyuwy7iXG8fTnh1nLw91zFnvsL4vL"};
        const vector<string> share = {"100"};
        
        //only if u want to generate a preview_gif or combine video + audio
        const int firstMedia = 0;
        const int numbOfMediaToGen = 10;
        //only if u want to generate a preview_gif
        const int fps = 30;
        //only if u want to combine video + audio
        const string inputVideoForm = "mp4";
        const string inputAudioForm = "mp3";
        const string outputVideoForm = "mp4";
        
        
        //from here u can ignore all
        const string chain = argv[1];
        string utility = "NULL";
        vector<vector<vector<string>>> singleLayer((int)collectionSize.size());
        vector<vector<vector<string>>> metadataSingleLayerName((int)collectionSize.size());
        vector<vector<vector<int>>> rarityWeight((int)collectionSize.size());
        vector<string> dnaOfAllMedia;
        vector<int> randomIndex;
        
        isPossibleToGenerateAllTheCollections(unique, collectionSize, layerDir);
        
        convertCollectionSize(collectionSize); 
        randomIndex.resize(collectionSize[(int)collectionSize.size()-1]);
        dnaOfAllMedia.resize(collectionSize[(int)collectionSize.size()-1]);
        addEmptyTrackAudioToVideos(); //it is preferable to uncomment this line if u are working with files without an audio track
        if(argc==2){
            if((int)collectionSize.size()>=1){
                deleteAllFilesOfFolder("./tmp");
                deleteAllFilesOfFolder("./output/media");
                deleteAllFilesOfFolder("./output/json");
                deleteAllFilesOfFolder("./output/video_with_audio");
                deleteFile("./output/preview_gif.gif");
                for(int i=1;i<(int)collectionSize.size();++i){
                    readLayersAndRaritys(layerDir[i-1], singleLayer[i-1], metadataSingleLayerName[i-1], rarityWeight[i-1], randomized);
                    if(randomized)
                        genAndSaveDnaRandomly(layerDir[i-1], singleLayer[i-1], collectionSize, i, dnaOfAllMedia, unique);
                    else
                        genAndSaveDnaWithRarity(layerDir[i-1], singleLayer[i-1], rarityWeight[i-1], collectionSize, i, dnaOfAllMedia, unique);
                }
                createRarityFile("./output/rarity_list.txt", collectionSize[(int)collectionSize.size()-1]);
                deleteCharactersFromDnas(dnaOfAllMedia);
                for(int i=1;i<(int)collectionSize.size();++i){
                    if(chain=="SOL")
                        generateAllMediaSolanaMetadata(layerDir[i-1], metadataSingleLayerName[i-1], name, description, symbol, family, sellerFeeBasisPoints, externalUrl, address, share, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                    else
                        generateAllMediaMetadata(layerDir[i-1], metadataSingleLayerName[i-1], name, description, baseUri, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                    generateAllMedia(layerDir[i-1], singleLayer[i-1], collectionSize, i, scale, dnaOfAllMedia, outputFormat, chain);
                }
                if(shuffleOutput){
                    createShuffleFile(collectionSize[(int)collectionSize.size()-1]);
                    readRandomIndex(randomIndex, chain);
                    shuffleCollection(randomIndex, name, baseUri, outputFormat, chain, collectionSize[(int)collectionSize.size()-1]);
                }
                generateMetadataJson(collectionSize[(int)collectionSize.size()-1], chain);
            }
            else
                cerr << "error: the collection is empty" << endl;
        }
        else{
            utility = argv[2];
            
            if(utility=="update_info"){
                deleteAllFilesOfFolder("./output/json");
                readDnaFromFile(dnaOfAllMedia);
                deleteCharactersFromDnas(dnaOfAllMedia);
                for(int i=1;i<(int)collectionSize.size();++i){
                readLayersAndRaritys(layerDir[i-1], singleLayer[i-1], metadataSingleLayerName[i-1], rarityWeight[i-1], randomized);
                    if(chain=="SOL")
                        generateAllMediaSolanaMetadata(layerDir[i-1], metadataSingleLayerName[i-1], name, description, symbol, family, sellerFeeBasisPoints, externalUrl, address, share, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                    else
                        generateAllMediaMetadata(layerDir[i-1], metadataSingleLayerName[i-1], name, description, baseUri, extraMetadata, collectionSize, i, dnaOfAllMedia, outputFormat);
                }
                if(shuffleOutput){
                    readRandomIndex(randomIndex, chain);
                    reversePrevShuffle(chain, collectionSize[(int)collectionSize.size()-1], randomIndex, outputFormat);
                    shuffleCollection(randomIndex, name, baseUri, outputFormat, chain, collectionSize[(int)collectionSize.size()-1]);
                }
                generateMetadataJson(collectionSize[(int)collectionSize.size()-1], chain);
            }
            else if(utility=="preview_gif")
                generatePreviewGif(firstMedia, numbOfMediaToGen, scale, fps);
            else if(utility=="combine_video_with_audio")
                mergeAllAudioWithVideo(firstMedia, inputVideoForm, inputAudioForm, outputVideoForm, numbOfMediaToGen);
            else{
                cerr << "parameters invalid, check your input" << endl;
                
            }
        }
    }
    else
        cerr << "number of parameters invalid, check your input" << endl;
 return 0;
}

/*
    exit(1) -> for ffmpeg error
    exit(2) -> for reading / writing operation from file
    exit(3) -> for some user input error
*/
