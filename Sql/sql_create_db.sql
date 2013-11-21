-- Enable foreign keys support
PRAGMA foreign_keys = ON;

-------------------------------------------------------------------------------
CREATE TABLE dataset
(
        id    INTEGER PRIMARY KEY,
        hash  TEXT NOT NULL,
        alias TEXT
);

-------------------------------------------------------------------------------
CREATE TABLE tag
(
        id    INTEGER PRIMARY KEY,
        label TEXT NOT NULL DEFAULT 'Label'
);

CREATE UNIQUE INDEX idx_tag_label ON tag( label );

-------------------------------------------------------------------------------
CREATE TABLE tag_node
(
        id        INTEGER PRIMARY KEY,
        parent_id INTEGER REFERENCES tag_node( id ),
        tag_id    INTEGER NOT NULL REFERENCES tag( id ),
        level     INTEGER,
        path      TEXT
);

CREATE INDEX idx_tag_node_tid ON tag_node( tag_id );

-------------------------------------------------------------------------------
CREATE TABLE dataset_membership(
        -- id              INTEGER PRIMARY KEY,
        dataset_id INTEGER NOT NULL REFERENCES dataset( id ),
        tag_id     INTEGER NOT NULL REFERENCES tag( id ),
        PRIMARY KEY( dataset_id, tag_id )
);

CREATE INDEX idx_ds_membership_dataset_id ON dataset_membership( dataset_id );
CREATE INDEX idx_ds_membership_dataset_tag_id ON dataset_membership( tag_id );

-------------------------------------------------------------------------------
CREATE TABLE dataset_attribute
(
        id         INTEGER PRIMARY KEY,
        dataset_id INTEGER NOT NULL REFERENCES dataset( id ),
        rank       INTEGER NOT NULL,
        name       TEXT NOT NULL,
        value      TEXT
);

CREATE INDEX idx_dataset_attribute_dsid ON dataset_attribute( dataset_id );
